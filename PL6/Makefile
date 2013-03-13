# Makefile
CC = g++ 
INCLUDE=-I ./include -L ./.libs
LIBS=-lxapian -lz -luuid

bio_indexer: bio_indexer.cc
	$(CC) $(INCLUDE) -o $@ $< $(LIBS)

clean: 
	rm -rf bio_indexer
