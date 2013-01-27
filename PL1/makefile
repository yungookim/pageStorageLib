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
	echo "total_size\tblock_size\to_sync\tno_o_sync"   >> ./graph/data.tsv
	./create_random_file 0.test 104857600 10485760     >> ./graph/data.tsv
	./create_random_file 1.test 104857600 1048576      >> ./graph/data.tsv
	rm ./1.test
	./create_random_file 2.test 104857600 104857       >> ./graph/data.tsv
	rm ./2.test
	./create_random_file 3.test 104857600 1048         >> ./graph/data.tsv
	rm ./3.test
	./create_random_file 4.test 104857600 104          >> ./graph/data.tsv
	rm ./4.test
	./create_random_file 5.test 104857600 10           >> ./graph/data.tsv
	rm ./5.test
	./create_random_file 6.test 104857600 1            >> ./graph/data.tsv
	rm ./6.test
