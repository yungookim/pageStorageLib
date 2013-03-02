CC = g++ 
OPTS =  -lpthread ./libleveldb.a -I ./include

all: read write csv2leveldb
	
read: read.cc
	$(CC) -o read read.cc $(OPTS)

write: write.cc
	$(CC) -o write write.cc $(OPTS)

csv2leveldb: csv2leveldb.cc
	$(CC) -o csv2leveldb csv2leveldb.cc $(OPTS)

clean:
	rm -rf read write leveldb_dir

test: all
	./write
	./read
