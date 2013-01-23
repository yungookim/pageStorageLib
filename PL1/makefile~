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
	rm ./graph/data.tsv
	echo "total_size\t block_size\t o_sync\t no_o_sync\n" >> ./graph/data.tsv
	./create_random_file 0.test 104857600 10485760 >> ./graph/data.tsv
	./create_random_file 1.test 1048576 1048576    >> ./graph/data.tsv
	./create_random_file 2.test 209715200 1048576  >> ./graph/data.tsv
	./create_random_file 3.test 209715200 10485760 >> ./graph/data.tsv
