# Makefile
CC = g++ 

all: library.o foo
	
foo: foo.cc
	$(CC) -o $@ library.o $<

test_foo: 
	make clean
	python mkrandom.py a.random 100
	# python mkrandom.py 1.random 5
	# python mkrandom.py 2.random 5
	# python mkrandom.py 3.random 5
	# python mkrandom.py 4.random 5
	# python mkrandom.py 5.random 5
	make && ./foo a.random a.test 100

clean: 
	rm -f foo library.o foo *.test