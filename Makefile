CFLAGS=-std=c99 -pedantic -Wall -Wextra

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

lexical_analyzer: lexical_analyzer.o
	gcc $(CFLAGS) lexical_analyzer.o -o lexical_analyzer

clean:
	rm *.o
	rm lexical_analyzer -f
