//
// Created by fakys on 15.10.2026.
//

#include <interrupt.h>

#include "avr_array.h"
#include "init_os_kernel.h"

bool os_kernel::registerInterruptSec(double sec, void (*handler)()) {
    if (os_kernel::kernel.interruptQueue.size < MAX_INTERRUPT_HANDLER_COUNT) {
        os_kernel::kernel.interruptQueue.elems[os_kernel::kernel.interruptQueue.size].handler = handler;
        os_kernel::kernel.interruptQueue.elems[os_kernel::kernel.interruptQueue.size].sec_timer = sec;
        os_kernel::kernel.interruptQueue.elems[os_kernel::kernel.interruptQueue.size].start_sec_timer = sec;
        os_kernel::kernel.interruptQueue.size+=1;
        return true;
    }
    return false;
}
