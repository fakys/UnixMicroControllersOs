//
// Created by fakys on 15.10.2026.
//
#include "uart_handler.h"


bool uart_handler(Handler *handlers, int handler_count) {

    while (1) {
        while (bufferReadyReadData() && readMassage(receiveMessage())) {
        }

        if (TRANSACTION_READY) {
            //Если сообщение было успешно прочитанно, начинаем его обработку
            for (int i = 0; i < handler_count; i++) {
                Handler handler = handlers[i];
                //todo сделанно костыльно
                //Если мы нашли команду
                if (prefixSearchString(&handler.command, &transaction_message)) {
                    clearTransactionContext();

                    //todo сделать аргументы
                    if (handler.handler() != 0) {
                        //Обработки
                    } else {
                        //Обработки
                    }

                    break;
                }
            }
        }
    }
    return false;
}


