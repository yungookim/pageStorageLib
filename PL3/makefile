# Makefile
CC = g++

.PHONY: all clean test test_run

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
	./csv2heapfile random_big a.test $(PG) 
	./csv2idxfile random_big b.test $(PG)
	./query a.test A Z $(PG) F 
	./query_idx_heapfile b.test A Z $(PG) F
	rm -f *.test

test_run :
	make test PG=1008
	make test PG=2012
	make test PG=3000
	make test PG=4000
	make test PG=5000
	make test PG=6000
	make test PG=7000
	make test PG=8000
	make test PG=9000
	make test PG=10000
	make test PG=11000
	make test PG=12000
	make test PG=13000

query_test : 
	make clean && make && ./csv2heapfile random heap_directory 50000 && ./query heap_directory A Z 50000

clean : 
	rm -f csv2heapfile query csv2idxfile query_idx_heapfile
	rm -f *.o
	rm -f heap_directory
	rm -f *.test
	rm -f _view
	rm -f view
