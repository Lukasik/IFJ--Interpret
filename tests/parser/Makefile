name=parser
CFLAGS=-std=c99 -pedantic -Wall -Wextra

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

test: test.o
	make -C ../../ $(name)
	gcc $(CFLAGS) ../../$(name).o ../../error.o test.o -o $(name)

clean:
	rm *.o -f
	rm *.diff -f
	rm */*.diff -f
	rm $(name) -f
	rm *.failed -f
