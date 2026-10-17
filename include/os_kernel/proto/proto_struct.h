//
// Created by fakys on 17.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_PROTO_STRUCT_H
#define UNIX_OPERATION_SYSTEM_PROTO_STRUCT_H
#include <stdint.h>

#include "avr_string.h"

typedef struct {
    uint8_t header_size;
    uint8_t soket_number;
    uint8_t status_code;
} ProtoHeader;

typedef struct {
    uint16_t body_size;
    String* body_message;
} ProtoBody;

typedef struct {
    ProtoHeader* header;
    ProtoBody* body;
} ProtoMessage;

#endif //UNIX_OPERATION_SYSTEM_PROTO_STRUCT_H
