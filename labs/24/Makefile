CC= gcc
CFLAGS= -Wall -pedantic -std=c99 -Isrc
LFLAGS= -lm

CMAINFILES= src/main.c
CTESTFILES= src/test.c src/test/test_tree.c
CCOMMONFILES= src/log/log.c src/token/token_io.c\
	src/token/token_queue.c src/token/token_sort_station.c\
	src/token/token_vector.c src/token/operation/operation.c\
	src/token/token_tree.c src/token/token_build_tree.c\
	src/token/token.c

main: $(CMAINFILES:.c=.o) $(CCOMMONFILES:.c=.o)
	$(CC) $(CFLAGS) $(CMAINFILES:.c=.o) $(CCOMMONFILES:.c=.o) -o main $(LFLAGS) 

test: $(CTESTFILES:.c=.o) $(CCOMMONFILES:.c=.o)
	$(CC) $(CFLAGS) $(CTESTFILES) $(CCOMMONFILES:.c=.o) -o test $(LFLAGS) 

.PHONY: clean
clean:
	rm -f $(CMAINFILES:.c=.o) $(CTESTFILES:.c=.o) $(CCOMMONFILES:.c=.o) Dependences

# Зависимости
Dependences:
	./update.sh
include Dependences
