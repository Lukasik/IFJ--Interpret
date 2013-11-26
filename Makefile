CFLAGS=-std=c99 -pedantic -Wall -Wextra -Wno-unused-parameter
.PHONY: scanner, parser

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

scanner: scanner.o error.o
	@echo

parser: parser.o error.o

parser-test: clean  error.o scanner.o ial.o garbage.o stack.o debug.o parser.o generator.o
	gcc *.o -o parser -g3

clean:
	@rm *.o parser -f > /dev/null
