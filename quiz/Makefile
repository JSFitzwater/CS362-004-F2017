CFLAGS = -Wall -fpic -coverage -lm

testme.o: testme.c
	gcc -c testme.c -g  $(CFLAGS)

testme: testme.o
	gcc -o testme testme.o $(CFLAGS)

clean:
	rm -f *.o