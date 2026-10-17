//
// Created by fakys on 17.10.2026.
//


#include "os_soket.h"

#include "init_os_kernel.h"


os_kernel::Soket *os_kernel::createSoket(uint8_t socket_type) {
    if (os_kernel::kernel.soketManager.soket_count >= MAX_SOKET_COUNT) {
        return nullptr;
    }
    Soket* soket = &(os_kernel::kernel.soketManager.all_soket[os_kernel::kernel.soketManager.soket_count]);

    soket->socket_type = socket_type;
    soket->soket_user_mod = kernel.userMod.user_mode_type;
    soket->soket_number = os_kernel::kernel.soketManager.soket_count;

    os_kernel::kernel.soketManager.soket_count += 1;

    return soket;
}

ProtoMessage* os_kernel::sendMessageOnSoket(Soket* soket, String* message, bool waiting_response) {
    if (soket->socket_type == UART_SOKET) {
        os_kernel::uartSendMessage(message);
        if (waiting_response) {
            return os_kernel::uartWaitingMessage();
        }
    }
    return nullptr;
}
