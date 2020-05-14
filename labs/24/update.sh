#!/bin/bash
# Обновляет зависимости файлов и запускает make
# Маленькая автоматизация, теперь не надо писать зависимости
CC="gcc"

# Находим исходные файлы
CFILES="$(find src -name *.c -type f | grep -v template)"

# Обновляем зависиомости
$CC -Isrc -MM $CFILES > Dependences