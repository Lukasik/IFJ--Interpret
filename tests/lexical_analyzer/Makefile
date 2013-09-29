name=lexical_analyzer
CFLAGS=-std=c99 -pedantic -Wall -Wextra

test: clean ../../$(name).o test.o
	gcc $(CFLAGS) ../../$(name).o test.o -o $(name)

clean:
	rm *.o -f
	rm *.diff -f
	rm */*.diff -f
	rm lexical_analyzer -f
	rm *.failed -f
