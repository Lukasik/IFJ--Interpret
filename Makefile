CFLAGS=-std=c99 -pedantic -Wall -Wextra

.PHONY: lexical_analyzer

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

lexical_analyzer: lexical_analyzer.o error.o

clean:
	rm *.o
