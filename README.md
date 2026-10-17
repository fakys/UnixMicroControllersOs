# UnixMicroControllersOs
## Компиляция
```
cmake -S . -B build
```
```
cd ./build && make
```



## Прошивка МК
### AVR 
#### Проверенно на atmega328p

```
`avrdude -c arduino -p m328p -P /dev/ttyUSB0 -U flash:w:unix_operation_system.hex:i`
```

#### Настройки порта для uart
```
stty -F /dev/ttyUSB0 -echo -icanon
```

## Проверка без MK
### AVR
Для проверки ос можно использовать simavr или их настройку simduino, я собирал из исходников версию 1.8
https://github.com/buserror/simavr/tree/v1.8, там ничего трудного, просто выполнить make файлы

Далее скомпилировать мое приложение и можно запустить эмулятор
```bash
simavr -g -m atmega328p -f 16000000 unix_operation_system.hex
```
В simavr я не нашел как можно работать с UART, так что единственное взаимодействие может быть только через gdb.
Ключ *-g* поднимает tcp сокет с портом 1234 и вы можете к нему подключится

```bash
    avr-gdb unix_operation_system
```
Далее подключаемся к порту 1234
```
    target remote :1234
```
Для работы с UART можно использовать их надстройку simduino, она так же лежит в их репозитории по пути `examples/board_simduino`
Компилируем и запускаем 
```bash
    simduino unix_operation_system.hex
```
Только теперь он создаст порты по которым можно обмениваться по UART, правда через gdb уже не подключишься 


## О прошивки 
Прошивка представляет из себя небольшую операционную систему для avr микро контроллеров, она предоставляет небольшой набор системных вызовов, файловую систему, центральное ядро с контролем памяти, UART протокол для обмена данными с контроллером, вот репозиторий контроллера https://github.com/fakys/MicroDeviceController