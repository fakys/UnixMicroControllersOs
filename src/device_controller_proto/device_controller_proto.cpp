//
// Created by fakys on 17.10.2026.
//

#include "device_controller_proto.h"

#include "init_os_kernel.h"

ProtoMessage* decodeMessage(String* message) {
    if (message->character[0] != 2) { //Сообщение ошибочное
        return nullptr;
    }

    if (message->size < 4) {
        return nullptr;
    }

    //Выделяем память
    ProtoHeader* header = (ProtoHeader*)os_kernel::allocate_memory(sizeof(ProtoHeader));
    ProtoBody* body = (ProtoBody*)os_kernel::allocate_memory(sizeof(ProtoBody));
    body->body_message = (String*)os_kernel::allocate_memory(sizeof(String));
    body->body_message->character = (uint8_t*)os_kernel::allocate_memory(sizeof(uint8_t)*UART_MAX_BUFFER_SIZE);
    body->body_message->reserve = UART_MAX_BUFFER_SIZE;
    ProtoMessage* proto_message = (ProtoMessage*)os_kernel::allocate_memory(sizeof(ProtoMessage));

    header->header_size = message->character[0];
    header->soket_number = message->character[1];
    header->soket_number = message->character[2];

    if (message->character[3] + message->character[0] != message->size) {
        os_kernel::clear_memory(body->body_message->character);
        os_kernel::clear_memory(body->body_message);
        os_kernel::clear_memory(body);
        os_kernel::clear_memory(header);
        os_kernel::clear_memory(proto_message);
        return nullptr;
    }

    for (int i = 0; i < message->character[3]; i++) {
        uint8_t byte = message->character[i+3];
        appendStringByte(body->body_message, byte);
    }


    //Парсим сообщение
    return proto_message;
};

ProtoMessage* encodeMessage(uint8_t soket_num, uint8_t status_code, String* message) {
    ProtoHeader* header = (ProtoHeader*)os_kernel::allocate_memory(sizeof(ProtoHeader));
    ProtoBody* body = (ProtoBody*)os_kernel::allocate_memory(sizeof(ProtoBody));
    body->body_message = message;
    ProtoMessage* proto_message = (ProtoMessage*)os_kernel::allocate_memory(sizeof(ProtoMessage));

    header->header_size = 2;
    header->soket_number = soket_num;
    header->status_code = status_code;

    return proto_message;
};


String* protoMessageToString(ProtoMessage* proto) {
    if (proto->body->body_message->size != proto->body->body_size) {
        return nullptr;
    }

    String* string = (String*)os_kernel::allocate_memory(sizeof(String));
    string->character = (uint8_t*) os_kernel::allocate_memory(sizeof(uint8_t) * UART_MAX_BUFFER_SIZE + 2);
    appendStringByte(string, PROTO_BYTE_START);
    appendStringByte(string, proto->header->header_size);
    appendStringByte(string, proto->header->soket_number);
    appendStringByte(string, proto->header->status_code);

    appendStringByte(string, proto->body->body_size);

    for (int i = 0; i < proto->body->body_message->size; i++) {
        appendStringByte(string, proto->body->body_message->character[i]);
    }
    appendStringByte(string, PROTO_BYTE_END);

    return string;
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
