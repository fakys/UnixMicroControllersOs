//
// Created by fakys on 10.08.2026.
//

#ifndef AVR_PROTO_UART_HENDLER_H
#define AVR_PROTO_UART_HENDLER_H

#include <uart.h>
#include <uart_proto.h>
#include "../data_types/avr_string.h"

typedef int (*hand)();

typedef struct {
    String command;
    hand handler;
} Handler;


bool uart_handler(Handler *handlers, int handler_count);


#endif //AVR_PROTO_UART_HENDLER_H
