//
// Created by fakys on 16.10.2026.
//
#include "memory_controller.h"

#include "interrupt.h"


static os_kernel::MemoryController memory_controller;


os_kernel::MemoryController* os_kernel::init_memory_controller() {
    //todo сюда надо поместить размер стека

    return &memory_controller;
}

//Создаем элемент кучи
os_kernel::HeapElement* createHeapElement() {
    size_t heap_elem_size = sizeof(os_kernel::HeapElement);
    if (memory_controller.heap_element_count >= memory_controller.heap_all_element_count) {
        void* heap_result;
        memory_controller.heap_element_count += 1;
        memory_controller.heap_all_element_count += 1;
        if (memory_controller.heap) {
            heap_result = realloc(memory_controller.heap, heap_elem_size * memory_controller.heap_element_count);
        } else {
            heap_result = malloc(heap_elem_size * memory_controller.heap_element_count);
        }

        if (!heap_result) {
            memory_controller.heap_element_count -= 1;
            memory_controller.heap_all_element_count -= 1;
            return nullptr;
        }
        memory_controller.heap = (os_kernel::HeapElement*)heap_result;
    }

    return &memory_controller.heap[memory_controller.heap_element_count - 1];
};

void* os_kernel::allocate_memory(size_t size) {
    //todo проверять есть ли у нас ресурсы
    //выделяем память в куче
    void* elem = malloc(size);

    os_kernel::HeapElement* heap_elem = createHeapElement();
    if (!heap_elem) {
        return nullptr;
    }

    heap_elem->element = elem;
    heap_elem->use_memory = size;

    return elem;
}

//Очистка без освобождения
void os_kernel::clear_memory(void* elem) {
    bool bias = false;
    for (unsigned int i = 0; i < memory_controller.heap_element_count; i++) {
        if (memory_controller.heap[i].element == elem) { //Если ссылки на этементы равны, удаляем его но память не ощичаем!
            free(memory_controller.heap[i].element);
            memory_controller.heap[i].element = nullptr; //Удаляем и освобождаем память от элемента
            bias = true;
        }
        if (bias) {
            memory_controller.heap[i - 1] = memory_controller.heap[i];
            if (i == memory_controller.heap_element_count) { //Последний элемент очищаем
                memory_controller.heap[i].element = nullptr;
                memory_controller.heap[i].use_memory = 0;
            }
        }
    }

    memory_controller.heap_element_count -= 1;
}

//Очистка элементов кучи
bool os_kernel::freeHeapMemory() {
    os_kernel::HeapElement* heap_result;
    heap_result = (os_kernel::HeapElement*)realloc(memory_controller.heap, sizeof(os_kernel::HeapElement) * memory_controller.heap_element_count);
    if (!heap_result) {
        return false;
    }
    memory_controller.heap = heap_result;
    return true;
}