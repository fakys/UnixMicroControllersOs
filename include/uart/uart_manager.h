//
// Created by fakys on 17.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_UART_MANAGER_H
#define UNIX_OPERATION_SYSTEM_UART_MANAGER_H
#include "abstract_proto.h"

namespace os_kernel {
    typedef struct {
        os_kernel::AbstractProto *proto;
        int baud_rate;
    } UartManager;

    void initUartManager();
    bool uartSendMessage(String* message);
    ProtoMessage* uartWaitingMessage();
}


#endif //UNIX_OPERATION_SYSTEM_UART_MANAGER_H
