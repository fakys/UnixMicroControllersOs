//
// Created by fakys on 16.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_INIT_OS_KERNEL_H
#define UNIX_OPERATION_SYSTEM_INIT_OS_KERNEL_H

#include <interrupt.h>
#include "memory_controller.h"
#include "os_soket.h"
#include "os_user_mod.h"
#include "uart_manager.h"

namespace os_kernel {
    typedef struct {
        os_kernel::InterruptQueue interruptQueue;
        os_kernel::MemoryController memoryController;
        os_kernel::UserMod userMod;
        os_kernel::SoketManager soketManager;
#ifdef USE_UART
        os_kernel::UartManager uartManager;
#endif
    } OsKernel;

    extern OsKernel kernel;

    int init_os_kernel();
}




#endif //UNIX_OPERATION_SYSTEM_INIT_OS_KERNEL_H
