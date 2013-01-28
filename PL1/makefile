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
	rm -f *.o create_random_file get_histogram > /dev/null 2>&1
	rm ./graph/*.tsv > /dev/null 2>&1
	rm *.test > /dev/null 2>&1

test:
	echo "total_size\tblock_size\ttime"   > ./graph/write.tsv
	./create_random_file 0.test 104857600 2      >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 4      >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 8      >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 16     >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 32     >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 64     >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 128    >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 256    >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 512    >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 1024   >> ./graph/write.tsv
	rm 0.test
	./create_random_file 0.test 104857600 2048   >> ./graph/write.tsv
	echo "total_size\tblock_size\ttime"   > ./graph/read.tsv
	./get_histogram 0.test 2                     >> ./graph/read.tsv
	./get_histogram 0.test 4                     >> ./graph/read.tsv
	./get_histogram 0.test 8                     >> ./graph/read.tsv
	./get_histogram 0.test 16                    >> ./graph/read.tsv
	./get_histogram 0.test 32                    >> ./graph/read.tsv
	./get_histogram 0.test 64                    >> ./graph/read.tsv
	./get_histogram 0.test 128                   >> ./graph/read.tsv
	./get_histogram 0.test 256                   >> ./graph/read.tsv
	./get_histogram 0.test 512                   >> ./graph/read.tsv
	./get_histogram 0.test 1024                  >> ./graph/read.tsv
	./get_histogram 0.test 2048                  >> ./graph/read.tsv
	rm ./0.test
