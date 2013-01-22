CC = gcc

all: create_random_file get_histogram 

library.o: library.c library.h
	$(CC) -o library.o -c library.c
 
create_random_file: create_random_file.c library.o
	$(CC) -o $@ $< library.o

get_histogram: get_histogram.c library.o
	$(CC) -o $@ $< library.o

.PHONY: clean

clean:  
	rm -f *.o create_random_file get_histogram
	rm *.test

test:
	./create_random_file 0.test 104857600 10485760
	./create_random_file 4.test 104857600 2048
	./create_random_file 1.test 1048576 1048576
	./create_random_file 2.test 209715200 1048576
	./create_random_file 3.test 209715200 10485760
