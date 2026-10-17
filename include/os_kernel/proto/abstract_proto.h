//
// Created by fakys on 17.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_ABSTRACT_PROTO_H
#define UNIX_OPERATION_SYSTEM_ABSTRACT_PROTO_H

#include "avr_string.h"
#include "os_soket.h"
#include "proto_struct.h"

namespace os_kernel {
    using AbstractProto = struct {
        uint8_t byteStart;
        uint8_t byteEnd;
        // Кодируем сообщение по правилам протокола
        ProtoMessage* (*encodeMessage)(uint8_t soket_num, uint8_t status_code, String* message);
        // Декодируем сообщение
        ProtoMessage* (*decodeMessage)(String* message);
        //Переводит структуру ProtoMessage в String
        String* (*protoMessageToString)(ProtoMessage* proto_message);

    };
}

#endif //UNIX_OPERATION_SYSTEM_ABSTRACT_PROTO_H
