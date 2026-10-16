//
// Created by fakys on 16.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_INIT_OS_KERNEL_H
#define UNIX_OPERATION_SYSTEM_INIT_OS_KERNEL_H

#include <interrupt.h>
#include "memory_controller.h"

namespace os_kernel {
    typedef struct {
        os_kernel::InterruptQueue interruptQueue;
        os_kernel::MemoryController memoryController;
    } OsKernel;

    extern OsKernel kernel;

    int init_os_kernel();
}




#endif //UNIX_OPERATION_SYSTEM_INIT_OS_KERNEL_H
