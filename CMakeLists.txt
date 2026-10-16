cmake_minimum_required(VERSION 3.28)
project(unix_operation_system)

set(CMAKE_C_COMPILER avr-gcc)
set(MCU atmega328p)
set(F_CPU 16000000UL)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_COMPILER avr-gcc)
set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_ASM_COMPILER avr-gcc)
set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_SIZE avr-size)

add_definitions(-D__AVR_ATmega328P__=1)
add_definitions(-DF_CPU=16000000UL)
add_definitions(-DCPU_RATE=16000000)
add_definitions(-DSTEP_INTERRUPT=0.1)

add_executable(unix_operation_system
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/src/os_kernel.cpp
        ${CMAKE_SOURCE_DIR}/src/proto/uart_handler.cpp
        ${CMAKE_SOURCE_DIR}/src/proto/uart_proto.cpp
        ${CMAKE_SOURCE_DIR}/src/uart/uart.cpp
        ${CMAKE_SOURCE_DIR}/src/data_types/avr_string.cpp
        ${CMAKE_SOURCE_DIR}/src/data_types/avr_array.cpp
        ${CMAKE_SOURCE_DIR}/src/os_kernel/interrupt.cpp
        ${CMAKE_SOURCE_DIR}/src/os_kernel/init_os_kernel.cpp
        ${CMAKE_SOURCE_DIR}/src/os_kernel/os_kernel.cpp
        ${CMAKE_SOURCE_DIR}/src/os_kernel/memory_controller.cpp
)

target_link_options(unix_operation_system PRIVATE "-Wl,-Map=output.map -fno-threadsafe-statics")

#todo костыльное решение, т.к без этого подхватывается /usr/lib/gcc/avr/7.3.0/avr5/libgcc.a - а тут имножение только для 8 бит
target_link_libraries(unix_operation_system /usr/lib/gcc/avr/7.3.0/libgcc.a)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mmcu=${MCU} -DF_CPU=${F_CPU} -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mmcu=${MCU}")


target_include_directories(
        unix_operation_system PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/include/proto
        ${CMAKE_SOURCE_DIR}/include/helpers
        ${CMAKE_SOURCE_DIR}/include/os_kernel
        ${CMAKE_SOURCE_DIR}/include/uart
        ${CMAKE_SOURCE_DIR}/include/data_types
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom
        $<TARGET_FILE:${PROJECT_NAME}>
        ${PROJECT_NAME}.hex
        COMMENT "hex сформирован"
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND du ${PROJECT_NAME}.hex
)
