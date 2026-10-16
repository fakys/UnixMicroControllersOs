//
// Created by fakys on 15.10.2026.
//

#ifndef UNIX_OPERATION_SYSTEM_ARRAY_H
#define UNIX_OPERATION_SYSTEM_ARRAY_H

#include <stdint.h>

typedef struct {
    uint8_t* elem; //Ссылка
    int size; //Размер
    int reserve; //Сколько выделенно памяти
} Array;


bool appendArrayByte(Array* str, uint8_t byte);


#endif //UNIX_OPERATION_SYSTEM_ARRAY_H
