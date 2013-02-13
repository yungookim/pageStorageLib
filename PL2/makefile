# Makefile
CC = g++

all: foo write_fixed_len_pages read_fixed_len_page
library.o : library.cc library.h
	$(CC) -o $@ -c library.cc

foo : foo.cc library.o
	$(CC) -o $@ $< library.o

write_fixed_len_pages : write_fixed_len_pages.cc library.o
	$(CC) -o $@ $< library.o

read_fixed_len_page : read_fixed_len_page.cc library.o
	$(CC) -o $@ $< library.o

debug : foo.cc library.o
	g++ -g library.cc library.h foo.cc -o foo
	g++ -g library.cc library.h write_fixed_len_pages.cc -o write_fixed_len_pages
	
.PHONY: clean

clean : 
	rm -rf foo write_fixed_len_pages
	rm *.o
	rm *.test
