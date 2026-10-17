//
// Created by fakys on 17.10.2026.
//

#ifndef UNIX_MICRO_CONTROLLERS_OPERATION_SYSTEM_OS_SOKET_H
#define UNIX_MICRO_CONTROLLERS_OPERATION_SYSTEM_OS_SOKET_H
#include <stdint.h>

#include "avr_string.h"
#include "unix_os.h"
#include "proto/abstract_proto.h"

#define UART_SOKET 1

namespace os_kernel {
    typedef struct {
        uint8_t soket_number;
        uint8_t socket_type;
        uint8_t soket_user_mod;
    } Soket;

    typedef struct {
        Soket all_soket[MAX_SOKET_COUNT];
        uint8_t soket_count;
    } SoketManager;

    Soket* createSoket(uint8_t socket_type, AbstractProto* proto);
    ProtoMessage* sendMessageOnSoket(Soket* soket, String* message, bool waiting_response);
}

#endif //UNIX_MICRO_CONTROLLERS_OPERATION_SYSTEM_OS_SOKET_H
