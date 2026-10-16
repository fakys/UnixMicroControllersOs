//
// Created by fakys on 12.08.2026.
//

#ifndef AVR_PROTO_CHAR_HELPER_H
#define AVR_PROTO_CHAR_HELPER_H

#include <stdint.h>



typedef struct {
    uint8_t* character; //Ссылка
    int size; //Размер
    int reserve; //Сколько выделенно памяти
} String;


bool appendByte(String* str, uint8_t byte);

bool unshiftByte(String* str, uint8_t byte);

//Сравнивет префиксы строк
bool prefixSearchString(String* search, String* str);
#endif //AVR_PROTO_CHAR_HELPER_H
