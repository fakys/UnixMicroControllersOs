//
// Created by fakys on 15.10.2026.
//

#include "avr_array.h"

bool appendArrayByte(Array* str, uint8_t byte) {
    if (str->size >= str->reserve) {
        return false;
    }
    str->elem[str->size] = byte;
    str->size = str->size + 1;
    return true;
}