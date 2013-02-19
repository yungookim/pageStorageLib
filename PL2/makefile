# Makefile
CC = g++

all : library.o write_fixed_len_pages read_fixed_len_pages heap_test

library : library.cc library.h
	$(CC) -o $@ -c

foo : foo.cc
	$(CC) -o $@ $< library.o

write_fixed_len_pages : write_fixed_len_pages.cc
	$(CC) -o $@ $< library.o

read_fixed_len_pages : read_fixed_len_pages.cc
	$(CC) -o $@ $< library.o

heap_test : 
	$(CC) library.o heap_test.cc -o heap_test

debug : foo.cc library.o read_fixed_len_pages.o
	g++ -g library.cc library.h foo.cc -o foo
	g++ -g library.cc library.h write_fixed_len_pages.cc -o write_fixed_len_pages
	g++ -g library.cc library.h read_fixed_len_pages.cc -o read_fixed_len_pages
	
.PHONY: clean

clean : 
	rm -rf foo write_fixed_len_pages read_fixed_len_pages heap_test
	rm *.o
	rm heap_directory
	rm *.test