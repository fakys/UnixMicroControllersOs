//
// Created by fakys on 15.10.2026.
//

#include "avr_string.h"
#include <util/delay.h>

bool appendByte(String* str, uint8_t byte) {
    if (str->size >= str->reserve) {
        return false;
    }
    str->character[str->size] = byte;
    str->size = str->size + 1;
    return true;
}

bool unshiftByte(String* str, uint8_t byte) {
    if (str->size >= str->reserve) {
        return false;
    }
    for (int index = 0; index < str->size; index++) {
        str->character[index+1] = str->character[index];
    }
    str->character[0] = byte;
    str->size = str->size + 1;
    return true;
}

//Сравнивет префиксы строк
bool prefixSearchString(String* search, String* str) {
    if (search->size > str->size) {
        return false;
    }

    bool exists = true;
    for (int index = 0; index < search->size; index++) {
        if (search->character[index] != str->character[index]) { //Если префиксы у строк не равны
            exists = false;
        }
    }
    return exists;
}