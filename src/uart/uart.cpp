//
// Created by fakys on 15.10.2026.
//

#include "uart.h"


bool dataSuccessSend() {
    return (UCSR0A & (1 << TXC0));
}

//Проверяем пуст ли буфер и можем ли мы отправлять новый кадр
bool checkTransferBuffer() {
    return (UCSR0A & (1 << UDRE0));
}

bool sendMessage(uint8_t byte) {
    //Отправляем наш бит
    UDR0 = byte;

    return true;
}
//Вернет true когда буфер будет готов к чтению
bool bufferReadyReadData() {
    return (UCSR0A & (1 << RXC0));
};

void initUart(int baud_rate) {
    UBRR0H = (baud_rate >> 8);
    UBRR0L = baud_rate;

    //Включаем передачу и получение данных
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

uint8_t receiveMessage() {
    return UDR0;
}

