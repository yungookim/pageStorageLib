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
	./create_random_file 0.test 104857600 10485760
	./create_random_file 1.test 1048576 1048576
	./create_random_file 2.test 209715200 1048576
	./create_random_file 3.test 209715200 10485760
