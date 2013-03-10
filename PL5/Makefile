# Makefile
CC = g++ 

all: library.o foo
	
foo: foo.cc
	$(CC) -o $@ library.o $<

test_foo: 
	python mkrandom.py a.random 100
	make && ./foo a.random a.test 100

clean: 
	rm -f foo library.o foo *.random *.test