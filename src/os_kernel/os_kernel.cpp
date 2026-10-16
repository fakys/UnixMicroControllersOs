//
// Created by fakys on 16.10.2026.
//

#include "os_kernel.h"
#include <unix_os.h>
#include <util/delay.h>


void os_kernel::checkOsKernelState() {
    PORTB |= (1 << PB5);
    _delay_ms(100);

    PORTB &= ~(1 << PB5);
}

