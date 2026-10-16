//
// Created by fakys on 16.10.2026.
//


#include "init_os_kernel.h"

#include "os_kernel.h"
#include <unix_os.h>
// #include <util/delay.h>
#include <util/delay.h>

#include "memory_controller.h"

os_kernel::OsKernel os_kernel::kernel;


ISR(TIMER1_COMPA_vect) {
    for (int i = 0; i < os_kernel::kernel.interruptQueue.size; i++) {
        os_kernel::InterruptElement* elem = &os_kernel::kernel.interruptQueue.elems[i];
        elem->sec_timer -= STEP_INTERRUPT;
        if (elem->sec_timer <= 0) {
            (*elem->handler)();
            elem->sec_timer = elem->start_sec_timer;
        }
    }
}

void init_interrupts() {
    DDRB |= (1 << PB5);

    // выставляем каждые 100 mc если FRE_OS_KERNEL 6250
    OCR1A = FRE_OS_KERNEL;
    TIMSK1 |= (1 << OCIE1A);
    TCCR1B = (1 << CS12);
    sei();
}

int os_kernel::init_os_kernel() {
    os_kernel::init_memory_controller();

    //Базовое прерываение на проверку состояния ядра
    os_kernel::registerInterruptSec(0, &os_kernel::checkOsKernelState);

    init_interrupts();
    return 0;
}
