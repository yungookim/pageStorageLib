# Makefile
CC = g++ 

all: library.o foo
	
foo: foo.cc
	$(CC) -o $@ library.o $<

clean: 
	rm -f foo library.o foo