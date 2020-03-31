CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -Iinclude
OBJECTS=objects/log.o objects/vector.o

all: cp7

test: lib
	$(CC) $(CFLAGS) src/test/*.c src/matrix.c $(OBJECTS) -g -o test.out

cp7: lib
	$(CC) $(CFLAGS) src/main.c src/matrix.c $(OBJECTS) -o main.out

lib: include/log/log.c vector/vector.c

include/log/log.c:
	$(CC) -c $(CFLAGS) include/log/log.c -o objects/log.o

vector/vector.c:
	$(CC) -c $(CFLAGS) src/vector/vector.c -o objects/vector.o