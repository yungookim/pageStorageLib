# Makefile
CC = g++

all : library.o write_fixed_len_pages read_fixed_len_pages heap_test csv2heapfile heapfile2csv query

library : library.cc library.h
	$(CC) -o $@

foo : foo.cc
	$(CC) -o $@ $< library.o

write_fixed_len_pages : write_fixed_len_pages.cc
	$(CC) -o $@ $< library.o

read_fixed_len_pages : read_fixed_len_pages.cc
	$(CC) -o $@ $< library.o

csv2heapfile : csv2heapfile.cc
	$(CC) -o $@ $< library.o

heapfile2csv : heapfile2csv.cc
	$(CC) -o $@ $< library.o
        
heap_test : 
	$(CC) library.o heap_test.cc -o heap_test
	$(CC) library.o record_iterator_test.cc -o record_iterator_test

query : query.cc
	$(CC) library.o query.cc -o query

debug : foo.cc library.o read_fixed_len_pages.o
	g++ -g library.cc library.h foo.cc -o foo
	g++ -g library.cc library.h write_fixed_len_pages.cc -o write_fixed_len_pages
	g++ -g library.cc library.h read_fixed_len_pages.cc -o read_fixed_len_pages
	g++ -g library.cc library.h csv2heapfile.cc -o csv2heapfile
	g++ -g library.cc library.h heapfile2csv.cc -o heapfile2csv
	
.PHONY: clean

clean : 
	rm -f foo write_fixed_len_pages read_fixed_len_pages heap_test csv2heapfile heapfile2csv record_iterator_test query
	rm -f *.o
	rm -f heap_directory
	rm -f *.test
	rm -f _view
	rm -f view
