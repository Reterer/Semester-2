CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -Isrc

CFILES = src/main.c src/command/command.c src/help/help.c src/list/int_list.c
CTESTFILES = src/test.c src/tests/test_list.c
CCOMMONFILES = src/log/log.c

CFILES_OBJ = $(CFILES:.c=.o)
CTESTFILES_OBJ = $(CTESTFILES:.c=.o)
CCOMMONFILES_OBJ = $(CCOMMONFILES:.c=.o)

main: $(CFILES_OBJ) $(CCOMMONFILES_OBJ)
	$(CC) $(CFLAGS) $(CFILES_OBJ) $(CCOMMONFILES_OBJ) -o main

test: $(CTESTFILES_OBJ) $(CCOMMONFILES_OBJ)
	$(CC) $(CFLAGS) $(CTESTFILES_OBJ) $(CCOMMONFILES_OBJ) -o test

.PHONY: clean
clean:
	rm -f $(CFILES_OBJ) $(CTESTFILES_OBJ) $(CCOMMONFILES_OBJ)

# Создание объектных файлов
src/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

# Зависимости
src/main.o: src/command/command.h src/list/int_list.h
src/command/command.o: src/command/command.h src/help/help.h src/log/log.h
src/help/help.o: src/help/help.h
src/log/log.o: src/log/log.h

# Можно было бы попробовать распихать объектные файлы
# По отдельным папкам, но лень.
# А так же можно попробовать генерировать 
# Зависимости с помощью команды $(CC) -Isrc -MM $<, но надо усложнять Makefile