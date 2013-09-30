CFLAGS=-std=c99 -pedantic -Wall -Wextra

.PHONY: scanner

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

scanner: scanner.o error.o

clean:
	rm *.o
