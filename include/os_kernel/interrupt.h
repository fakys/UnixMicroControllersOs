//
// Created by fakys on 15.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_INTERRUPT_H
#define UNIX_OPERATION_SYSTEM_INTERRUPT_H
#include <stdint.h>

#include "unix_os.h"

#define TIMER0 0


namespace os_kernel {
    typedef struct {
        void (*handler)();
        double sec_timer;
        double start_sec_timer;
    } InterruptElement;

    typedef struct {
        InterruptElement elems[MAX_INTERRUPT_HANDLER_COUNT]; //Ссылка
        uint8_t size; //Размер
        uint8_t timerNumber; //Номер таймера
    } InterruptQueue;

    bool registerInterruptSec(double sec, void (*handler)());
}


#endif //UNIX_OPERATION_SYSTEM_INTERRUPT_H
