CFLAGS=-Wall -std=c99 -pedantic -Iinclude
OBJECTS=objects/log.o objects/vector.o

cp7: lib
	gcc $(CFLAGS) src/*.c $(OBJECTS) -g -o main.out

test: lib
	gcc $(CFLAGS) src/test/*.c src/matrix.c $(OBJECTS) -g -o test.out

lib: objects/ objects/log.o objects/vector.o

objects/:
	mkdir objects

objects/log.o: include/log/log.c
	gcc -c $(CFLAGS) include/log/log.c -o objects/log.o

objects/vector.o: src/vector/vector.c
	gcc -c $(CFLAGS) src/vector/vector.c -o objects/vector.o