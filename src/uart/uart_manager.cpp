//
// Created by fakys on 17.10.2026.
//
#include "uart_manager.h"

#include "device_controller_proto.h"
#include "init_os_kernel.h"

void os_kernel::initUartManager() {
#ifdef USE_DEVICE_CONTROLLER_PROTO_FOR_UART
    kernel.uartManager.proto = device_controller_proto::create_device_controller_proto();
#endif
    kernel.uartManager.baud_rate = UART_BAUD_RATE;
    initUart(CPU_RATE / (16 * kernel.uartManager.baud_rate));
}

bool uartSendMessage(uint8_t soket_number, uint8_t status_code, String* message) {
    ProtoMessage* proto_message = os_kernel::kernel.uartManager.proto->encodeMessage(soket_number, status_code, message);
    if (!proto) {
        return false;
    }

    String* string = os_kernel::kernel.uartManager.proto->protoMessageToString(proto_message);

    if (!string) {
        return false;
    }

    for (uint8_t i = 0; i < string->size; i++) {
        //Проверяем можем ли мы отправлять новый кадр
        while (checkTransferBuffer()) {
            //todo timeout
        }

        sendMessage(string->character[i]); //Отправляем по одному байту

        //Проверяем что кадр был отправлен и принят
        while (dataSuccessSend()) {
            //todo timeout
        }
    }

    return false;
};

ProtoMessage* uartWaitingMessage() {
    String* str = (String*)os_kernel::allocate_memory(sizeof(String));
    str->character = (uint8_t*)os_kernel::allocate_memory(sizeof(uint8_t) * UART_MAX_BUFFER_SIZE);
    str->reserve = UART_MAX_BUFFER_SIZE;

    bool start_message = false;
    while (true) {
        //todo timeout
        if (bufferReadyReadData()) {
            uint8_t byte = receiveMessage();

            if (!start_message && byte == os_kernel::kernel.uartManager.proto->byteStart) {
                start_message = true;
                continue;
            } else if (start_message && byte != os_kernel::kernel.uartManager.proto->byteStart && byte != os_kernel::kernel.uartManager.proto->byteEnd) {
                if (str->size >= UART_MAX_BUFFER_SIZE) {
                    os_kernel::clear_memory(str->character);
                    os_kernel::clear_memory(str);
                    return nullptr;
                }
                appendStringByte(str, byte);
            } else if (start_message && byte == os_kernel::kernel.uartManager.proto->byteEnd) {
                break;
            } else {
                os_kernel::clear_memory(str->character);
                os_kernel::clear_memory(str);
                return nullptr;
            }
        }
    }

    return os_kernel::kernel.uartManager.proto->decodeMessage(str);
}

