# Makefile
CC = g++ 

all: library.o foo
	
foo: foo.cc
	$(CC) -o $@ library.o $<

test_foo: 
	make clean
	make && ./foo a.random a.test 100

make_randoms:
	python mkrandom.py a.random 100
	python mkrandom.py 1.random 5
	python mkrandom.py 2.random 5
	python mkrandom.py 3.random 5
	python mkrandom.py 4.random 5
	python mkrandom.py 5.random 5

clean: 
	rm -f foo library.o foo *.test

clean_files:
	rm -f *.random *.out