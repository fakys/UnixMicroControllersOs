
#include "uart_proto.h"

bool ACTIVE_TRANSACTION = false;
bool TRANSACTION_READY = false;

uint8_t transaction_context[MAX_TRANSACTION_SIZE] = "";
String transaction_message = {
    transaction_context,
    0,
    MAX_TRANSACTION_SIZE
};


bool readMassage(unsigned char byte) {
    if (ACTIVE_TRANSACTION) {
        if (byte == END_BYTE) {
            ACTIVE_TRANSACTION = false;
            TRANSACTION_READY = true;
            return false;
        }

        if (transaction_message.size >= MAX_TRANSACTION_SIZE) {
            return false;
        }
        appendByte(&transaction_message, byte);
        return true;
    }

    if (byte == START_BYTE) {
        ACTIVE_TRANSACTION = true;
        return true;
    }

    if (byte == END_BYTE) {
        ACTIVE_TRANSACTION = false;
    }

    return false;
}

bool createTransaction(String* message) {
    //todo Потом поправить это
    if (MAX_TRANSACTION_SIZE < message->size+2) {
        return false;
    }

    appendByte(&transaction_message, START_BYTE);
    for (int i = 0; i < message->size; i++) {
        appendByte(&transaction_message, message->character[i]);
    }
    appendByte(&transaction_message, END_BYTE);

    return true;
}

void clearTransactionContext() {
    ACTIVE_TRANSACTION = false;
    TRANSACTION_READY = false;

    //Очистка контекста
    for (int index = 0; index < MAX_TRANSACTION_SIZE; index++) {
        transaction_context[index] = '\0';
    }

    transaction_message.size = 0;
}

bool sendTransaction() {

    for (int i = 0; i < transaction_message.size; i++) {
        //todo timeout
        while (!checkTransferBuffer()) {

        }

        //Отправляем данные по транзакции
        sendMessage(transaction_message.character[i]);

        //todo timeout
        while (!dataSuccessSend()) {

        }
    }
    clearTransactionContext();
    return true;
}