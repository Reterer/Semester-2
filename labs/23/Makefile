CFILES = src/main.c src/enum/enum.c src/log/log.c src/tree/tree.c
CFLAGS = -Wall -pedantic -std=c99 -Isrc

release:
	gcc $(CFLAGS) $(CFILES) -o main.out

debug:
	gcc $(CFLAGS) $(CFILES) -g -o debug.out