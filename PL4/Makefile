# Makefile
CC = g++ 
OPTS =  -lpthread ./libleveldb.a -I ./include

all: read write csv2leveldb query_leveldb csv2idx_leveldb query_idx_leveldb
	
read: read.cc
	$(CC) -o read read.cc $(OPTS)

write: write.cc
	$(CC) -o write write.cc $(OPTS)

csv2leveldb: csv2leveldb.cc
	$(CC) -o $@ $< $(OPTS)

query_leveldb: query_leveldb.cc
	$(CC) -o $@ $< $(OPTS)

csv2idx_leveldb: csv2idx_leveldb.cc
	$(CC) -o $@ $< $(OPTS)

query_idx_leveldb: query_idx_leveldb.cc
	$(CC) -o $@ $< $(OPTS)

clean:
	rm -rf a read write query_leveldb csv2leveldb leveldb_dir query_idx_leveldb csv2idx_leveldb

test: all
	./write
	./read
