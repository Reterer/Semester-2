CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -Iinclude
OBJECTS=objects/log.o objects/vector.o

all: cp7

test: lib
	$(CC) $(CFLAGS) src/test/*.c src/matrix.c $(OBJECTS) -g -o test.out

cp7: lib
	$(CC) $(CFLAGS) src/*.c $(OBJECTS) -g -o main.out

lib: log.o vector.o

log.o: include/log/log.c
	$(CC) -c $(CFLAGS) include/log/log.c -o objects/log.o

vector.o: src/vector/vector.c
	$(CC) -c $(CFLAGS) src/vector/vector.c -o objects/vector.o