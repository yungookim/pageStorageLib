CC = gcc

default: create_random_file

library.o: library.c library.h
	$(CC) -o library.o -c library.c
 
create_random_file: create_random_file.c library.o
	$(CC) -o $@ $< library.o

.PHONY: clean

clean:  
	rm -f *.o create_random_file

test:
	./create_random_file test 100000 10
	./create_random_file test1 100000 100
	./create_random_file test2 100000 1000
	./create_random_file test3 100000 10000
	rm -f test test1 test2 test3

