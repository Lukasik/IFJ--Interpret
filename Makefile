CFLAGS=-std=c99 -pedantic -Wall -Wextra -Wno-unused-parameter -g3
.PHONY: scanner, parser

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

all: error.o scanner.o ial.o garbage.o stack.o debug.o parser.o generator.o inbuilt_functions.o
	gcc *.o -o ifj13

clean:
	@rm *.o ifj13 -f > /dev/null
