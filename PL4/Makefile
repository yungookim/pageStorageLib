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

bench: 
	@echo "Querying from A to..." 1>&2
	@for X in A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ; do \
		echo -n $$X 1>&2; \
		echo -n "\t" 1>&2; \
		time -f "%E\t%P" ./query_leveldb testdb1000000tuples A $$X ; \
	done

bench_and_log:
	make bench 2>1000000leveldb.bench 1>/dev/null

clean:
	rm -rf a read write query_leveldb csv2leveldb leveldb_dir query_idx_leveldb csv2idx_leveldb

test: all
	./write
	./read
