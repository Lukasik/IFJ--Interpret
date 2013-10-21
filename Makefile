CFLAGS=-std=c99 -pedantic -Wall -Wextra

.PHONY: scanner, parser

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

scanner: scanner.o error.o

parser: parser.o error.o

clean:
	rm *.o
