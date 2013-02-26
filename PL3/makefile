# Makefile
CC = g++

.PHONY: all clean test test_run bench bench_mark

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
	./csv2heapfile random a.test $(PG) 
	./csv2idxfile random b.test $(PG)
	./query a.test A Z $(PG) F 
	./query_idx_heapfile b.test A Z $(PG) F
	rm -f *.test

bench : 
	@echo "Query"
	@./query a.test A $(END) $(PG) F 
	@rm -f _view view
	@echo "============================="
	@echo "Idx query"
	@./query_idx_heapfile b.test A Z $(PG) F
	@rm -f _view view
	@echo "============================="

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


bench_mark :
	@./csv2heapfile random_huge a.test 131072
	@./csv2idxfile random_huge b.test 131072
	@echo "A to B"
	@make bench PG=131072 END=B
	@echo "A to C"
	@make bench PG=131072 END=C
	@echo "A to D"
	@make bench PG=131072 END=D
	@echo "A to E"
	@make bench PG=131072 END=E
	@echo "A to F"
	@make bench PG=131072 END=F
	@echo "A to G"
	@make bench PG=131072 END=G
	@echo "A to H"
	@make bench PG=131072 END=H
	@echo "A to I"
	@make bench PG=131072 END=I
	@echo "A to J"
	@make bench PG=131072 END=J
	@echo "A to K"
	@make bench PG=131072 END=K
	@echo "A to L"
	@make bench PG=131072 END=L
	@echo "A to M"
	@make bench PG=131072 END=M
	@echo "A to N"
	@make bench PG=131072 END=N
	@echo "A to O"
	@make bench PG=131072 END=O
	@echo "A to P"
	@make bench PG=131072 END=P
	@echo "A to Q"
	@make bench PG=131072 END=Q
	@echo "A to R"
	@make bench PG=131072 END=R
	@echo "A to S"
	@make bench PG=131072 END=S
	@echo "A to T"
	@make bench PG=131072 END=T
	@echo "A to U"
	@make bench PG=131072 END=U
	@echo "A to V"
	@make bench PG=131072 END=V
	@echo "A to W"
	@make bench PG=131072 END=W
	@echo "A to X"
	@make bench PG=131072 END=X
	@echo "A to Y"
	@make bench PG=131072 END=Y
	@echo "A to Z"
	@make bench PG=131072 END=Z

query_test : 
	make clean && make && ./csv2heapfile random heap_directory 50000 && ./query heap_directory A Z 50000

clean : 
	rm -f csv2heapfile query csv2idxfile query_idx_heapfile
	rm -f *.o
	rm -f heap_directory
	rm -f *.test
	rm -f _view
	rm -f view
