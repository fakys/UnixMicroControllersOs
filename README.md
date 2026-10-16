# Протокол дла микроконтроллеров AVR
## О протоколе

#### Данные передаются пока только через uart

#### Билд
```
cmake -S . -B build
```
```
cd ./build && make
```

#### Настройки порта
```
stty -F /dev/ttyUSB0 -echo -icanon
```
#### Прошивка МК
```
`avrdude -c arduino -p m328p -P /dev/ttyUSB0 -U flash:w:unix_operation_system.hex:i`
```

#### Для дебага 
```
valgrind --leak-check=full ./путь к файлу
```


#### Пример отправки ping
```
echo -en '\xffping\xfe' >> /dev/ttyUSB0
```