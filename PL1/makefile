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
	echo "total_size\tblock_size\ttime"   > ./graph/write.tsv
	./create_random_file 0.test 104857600 10485760     >> ./graph/write.tsv
	./create_random_file 1.test 104857600 1048576      >> ./graph/write.tsv
	rm ./1.test
	./create_random_file 2.test 104857600 104857       >> ./graph/write.tsv
	rm ./2.test
	./create_random_file 3.test 104857600 1048         >> ./graph/write.tsv
	rm ./3.test
	./create_random_file 4.test 104857600 104          >> ./graph/write.tsv
	rm ./4.test
	./create_random_file 5.test 104857600 10           >> ./graph/write.tsv
	rm ./5.test
	./create_random_file 6.test 104857600 1            >> ./graph/write.tsv
	rm ./6.test

	echo "total_size\tblock_size\ttime"   > ./graph/read.tsv
	./get_histogram 0.test 10485760     >> ./graph/read.tsv
	./get_histogram 0.test 1048576      >> ./graph/read.tsv
	./get_histogram 0.test 104857       >> ./graph/read.tsv
	./get_histogram 0.test 1048         >> ./graph/read.tsv
	./get_histogram 0.test 104          >> ./graph/read.tsv
	./get_histogram 0.test 10           >> ./graph/read.tsv
	./get_histogram 0.test 1            >> ./graph/read.tsv
	rm ./0.test



