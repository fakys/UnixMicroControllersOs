//
// Created by fakys on 16.10.2026.
//

#ifndef AVR_PROTO_MEMORY_CONTROLLER_H
#define AVR_PROTO_MEMORY_CONTROLLER_H
#include <unix_os.h>

#include "unix_os.h"

namespace os_kernel {
    typedef struct {
        size_t use_memory;
        void* element;
    } HeapElement;

    typedef struct {
        size_t all_memory = ALL_MEMORY;
        HeapElement* heap;
        uint16_t heap_element_count;
        uint16_t heap_all_element_count;
        size_t stack; //todo сделать, скорее всего придется через асемблер делать
    } MemoryController;

    MemoryController* init_memory_controller();

    void* allocate_memory(size_t size);
    void clear_memory(void* elem);
    bool freeHeapMemory(); //Очистка кучи
}


#endif //AVR_PROTO_MEMORY_CONTROLLER_H
