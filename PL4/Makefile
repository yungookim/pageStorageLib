CC = g++ 
OPTS =  -lpthread ./libleveldb.a -I ./include

all: read write
	
read: read.cc
	$(CC) -o read read.cc $(OPTS)

write: write.cc
	$(CC) -o write write.cc $(OPTS)

clean:
	rm -rf read write leveldb_dir

test: all
	./write
	./read
