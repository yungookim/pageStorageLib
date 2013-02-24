# Makefile
CC = g++

all : library.o csv2heapfile query csv2idxfile query_idx_heapfile

library : library.cc library.h
	$(CC) -o $@

csv2heapfile : csv2heapfile.cc
	$(CC) -o $@ $< library.o

query : query.cc
	$(CC) library.o query.cc -o query

csv2idxfile : 
	$(CC) library.o csv2idxfile.cc -o csv2idxfile

query_idx_heapfile :
	$(CC) library.o query_idx_heapfile.cc -o query_idx_heapfile

test_query : 
	./csv2heapfile random a.test 3000 && ./query a.test A Z 3000 F
	
test_idx_query : 
	./csv2idxfile random b.test 3000 && ./query_idx_heapfile b.test A Z 3000 F

test : 
	./csv2heapfile random a.test 1008
	./csv2idxfile random b.test 1008
	./query_idx_heapfile b.test A Z 1008 F

query_test : 
	make clean && make && ./csv2heapfile random heap_directory 50000 && ./query heap_directory A Z 50000

clean : 
	rm -f csv2heapfile query csv2idxfile query_idx_heapfile
	rm -f *.o
	rm -f heap_directory
	rm -f *.test
	rm -f _view
	rm -f view
