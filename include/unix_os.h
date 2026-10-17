//
// Created by fakys on 15.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_UNIX_OS_H
#define UNIX_OPERATION_SYSTEM_UNIX_OS_H

#include <uart/uart.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define MAX_INTERRUPT_HANDLER_COUNT 10
#define MAX_SOKET_COUNT 10
#define FRE_OS_KERNEL 6250
#define ALL_MEMORY 2048

int userMain();



#endif //UNIX_OPERATION_SYSTEM_UNIX_OS_H
