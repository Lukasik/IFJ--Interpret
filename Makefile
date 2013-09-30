CFLAGS=-std=c99 -pedantic -Wall -Wextra

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

lexical_analyzer: lexical_analyzer.o error.o
	gcc $(CFLAGS) lexical_analyzer.o error.o -o lexical_analyzer

clean:
	rm *.o
	rm lexical_analyzer -f
