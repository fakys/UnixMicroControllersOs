//
// Created by fakys on 17.10.2026.
//

#include "device_controller_proto.h"

#include "init_os_kernel.h"

ProtoMessage* decodeMessage(String* message) {

};

ProtoMessage* encodeMessage(uint8_t soket_num, uint8_t status_code, String* message) {

};


String* protoMessageToString(ProtoMessage* proto) {

}

os_kernel::AbstractProto* device_controller_proto::create_device_controller_proto() {
    static os_kernel::AbstractProto proto;
    proto.byteStart = PROTO_BYTE_START;
    proto.byteEnd = PROTO_BYTE_END;
    proto.decodeMessage = &decodeMessage;
    proto.encodeMessage = &encodeMessage;
    proto.protoMessageToString = &protoMessageToString;
    return &proto;
}
