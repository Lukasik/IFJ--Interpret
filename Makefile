CFLAGS=-std=c99 -pedantic -Wall -O3

.PHONY: scanner, parser

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

all: error.o scanner.o ial.o garbage.o stack.o debug.o parser.o generator.o inbuilt_functions.o
	gcc *.o -o ifj13 -O3

clean:
	@rm *.o ifj13 -f > /dev/null
