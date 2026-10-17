//
// Created by fakys on 17.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_DEVICE_CONTROLLER_PROTO_H
#define UNIX_OPERATION_SYSTEM_DEVICE_CONTROLLER_PROTO_H
#include "abstract_proto.h"

#define PROTO_BYTE_START 0xA1 //Байт начала приема сообщения
#define PROTO_BYTE_END 0xB1 //Байт окончания приема сообщения

namespace device_controller_proto {
    os_kernel::AbstractProto* create_device_controller_proto();
}

#endif //UNIX_OPERATION_SYSTEM_DEVICE_CONTROLLER_PROTO_H
