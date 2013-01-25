# Makefile
CC = g++ 

library.o : library.cc library.h
	$(CC) -o $@ -c library.cc

foo : foo.cc library.o
	$(CC) -o $@ $< library.o

.PHONY: clean

clean : 
	rm -rf foo
	rm *.o
