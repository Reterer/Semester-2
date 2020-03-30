CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -Iinclude
OBJECTS=objects/log.o

all: cp7

test: lib
	$(CC) $(CFLAGS) src/test/*.c $(OBJECTS) -o test.out

cp7: lib
	$(CC) $(CFLAGS) src/main.c src/matrix.c src/vector/vector.c $(OBJECTS) -o main.out

lib: include/log/log.c
	$(CC) -c $(CFLAGS) include/log/log.c -o objects/log.o
