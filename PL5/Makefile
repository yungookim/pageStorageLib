# Makefile
CC = g++ 
OPTS =  -lpthread ./libleveldb.a -I ./include

all: library.o foo msort bsort
	
foo: foo.cc
	$(CC) -o $@ library.o $<

msort: msort.cc
	$(CC) -o $@ library.o $<

bsort: bsort.cc
	$(CC) -o $@ $< $(OPTS)

test_msort: 
	make clean
	make
	python mkrandom.py a.random 10
	# <input_file> <out_file> <mem_capacity> <k>
	./msort a.random sorted.out 30 2

test_foo: 
	make clean
	make && ./foo a.random a.test 100

make_randoms:
	python mkrandom.py a.random 100
	python mkrandom.py 1.random 5
	python mkrandom.py 2.random 5
	python mkrandom.py 3.random 5
	python mkrandom.py 4.random 5
	python mkrandom.py 5.random 5
	
make_random_10mb:
	python mkrandom.py a.random 1000000

make_random_1mb:
	python mkrandom.py a.random 100000

bench_small_me:
	@make clean
	@make all
	@echo "K way sort."
	@echo "Mem_cap\tK\ttime"
	@for X in 10 20 30 40 50 60 70 80 90 100 ; do \
		echo -n 1024 1>&2; \
		echo -n "\t" 1>&2; \
		echo -n $$X 1>&2; \
		echo -n "\t" 1>&2; \
		time -f "%E" ./msort a.random sorted.out 1024 $$X; \
	done

# Plot the performances of different ways of sorting against 
# varying file sizes. Plot the performance of at least three ways 
# of sorting.
# 1. using bsort 
# 2. using msort with somewhat poorly chosen parameters 
# 3. using msort with a well tuned parameters
bench_compare:
	@make clean
	@make library.o msort bsort
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking..."
	@echo "fileSize\ttime" > bsort.bench
	@echo "fileSize\tmsort(Poor)\t" > msortPoor.bench
	@echo "fileSize\tmsort(Good)\t" > msortGood.bench
	@for X in 100000 200000 300000 400000 500000; do \
		echo "Sorting $$X tuples"; \
		python mkrandom.py a.random $$X; \
		echo -n "$$X\t" >> bsort.bench; \
		/usr/bin/time -f "%E" ./bsort a.random a.db 2>> bsort.bench; \
		echo -n "$$X\t" >> msortPoor.bench; \
		/usr/bin/time -f "%E" ./msort a.random sorted.out 100000 3 2>> msortPoor.bench; \
		echo -n "$$X\t" >> msortGood.bench; \
		/usr/bin/time -f "%E" ./msort a.random sorted.out 100000 10 2>> msortGood.bench; \
		# rm -rf a.db a.random sorted.out; \
	done
	@echo "Done"

clean: 
	rm -f foo library.o foo *.test msort bsort

cleanall:
	make clean
	rm -rf *.random *.out
	rm -rf *.db