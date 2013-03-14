# Makefile
CC = g++ 
INCLUDE=-I ./include -L ./.libs
LIBS=-lxapian -lz 

all: bio_indexer bio_search

bio_indexer: bio_indexer.cc
	$(CC) $(INCLUDE) -o $@ $< $(LIBS)

bio_search: bio_search.cc
	$(CC) $(INCLUDE) -o $@ $< $(LIBS)

clean: 
	rm -rf bio_indexer bio_search
