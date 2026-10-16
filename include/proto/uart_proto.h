//
// Created by fakys on 10.08.2026.
//

#ifndef AVR_PROTO_UART_PROTO_H
#define AVR_PROTO_UART_PROTO_H

#include "proto.h"
#include "uart.h"
#include "../data_types/avr_string.h"

extern bool ACTIVE_TRANSACTION;
extern bool TRANSACTION_READY;


extern uint8_t transaction_context[MAX_TRANSACTION_SIZE];
extern String transaction_message;

bool readMassage(unsigned char byte);

bool createTransaction(String* message);

void clearTransactionContext();

bool sendTransaction();



#endif //AVR_PROTO_UART_PROTO_H
