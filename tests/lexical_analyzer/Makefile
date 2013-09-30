name=lexical_analyzer
CFLAGS=-std=c99 -pedantic -Wall -Wextra

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: test.o
	make -C ../../ lexical_analyzer
	gcc $(CFLAGS) ../../$(name).o ../../error.o test.o -o $(name)

clean:
	rm *.o -f
	rm *.diff -f
	rm */*.diff -f
	rm lexical_analyzer -f
	rm *.failed -f
