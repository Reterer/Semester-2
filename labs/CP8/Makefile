CFILES = src/log/log.c src/command/command.c src/help/help.c src/list/int_list.c
CTESTFILES = src/log/log.c src/tests/test_list.c
CFLAGS = -Wall -pedantic -std=c99 -Isrc

cp8:
	gcc $(CFLAGS) $(CFILES) src/main.c -o main.out -g

test:
	gcc $(CFLAGS) $(CTESTFILES) src/test.c -o test.out