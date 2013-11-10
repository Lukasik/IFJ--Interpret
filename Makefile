CFLAGS=-std=c99 -pedantic -Wall -Wextra

.PHONY: scanner, parser

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

scanner: scanner.o error.o
	@echo

parser: parser.o error.o

parser-test: parser.o error.o scanner.o ial.o garbage.o
	gcc *.o -o parser -g3

clean:
	@rm *.o parser -f > /dev/null
