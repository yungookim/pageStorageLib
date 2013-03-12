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
	@python mkrandom.py a.random 1000000
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
bench_compare_msort_small:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_compare_msort_small 1024 3"
	@for X in 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000; do \
		echo -n "$$X\t"; \
		/usr/bin/time -f "%E" ./msort $$X.random sorted.out 1024 3 2>&1; \
		# rm -rf a.random sorted.out; \
	done
	@echo "Done"

bench_compare_msort_small_2:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_compare_msort_small_2 1024 5"
	@for X in 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000; do \
		echo -n "$$X\t"; \
		/usr/bin/time -f "%E" ./msort $$X.random sorted.out 1024 5 2>&1; \
		# rm -rf a.random sorted.out; \
	done
	@echo "Done"

bench_compare_msort_small_3:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_compare_msort_small_3 1024 5"
	@for X in 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000; do \
		echo -n "$$X\t"; \
		/usr/bin/time -f "%E" ./msort $$X.random sorted.out 10000 5 2>&1; \
		# rm -rf a.random sorted.out; \
	done
	@echo "Done"

bench_bsort_small:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_bsort_small"
	@echo "fileSize\ttime"
	@for X in 100000 200000 300000 400000 500000 600000 700000 800000 900000 1000000; do \
		echo -n "$$X\t";\
		/usr/bin/time -f "%E" ./bsort $$X.random a.db 2>&1; \
		rm -rf a.db; \
	done
	@echo "Done"

bench_msort_large:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_msort_large 1024 5"
	@for X in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do \
		echo -n "$$X\t"; \
		/usr/bin/time -f "%E" ./msort $$X.random sorted.out 1024 5 2>&1; \
		# rm -rf a.random sorted.out; \
	done
	@echo "Done"

bench_msort_large_2:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_msort_large_2 10000 5"
	@for X in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do \
		echo -n "$$X\t"; \
		/usr/bin/time -f "%E" ./msort $$X.random sorted.out 10000 5 2>&1; \
		# rm -rf a.random sorted.out; \
	done
	@echo "Done"

bench_bsort_large:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_bsort_large 1024 5"
	@for X in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000; do \
		echo -n "$$X\t";\
		/usr/bin/time -f "%E" ./bsort $$X.random a.db 2>&1; \
		rm -rf a.db; \
	done
	@echo "Done"

bench_bsort_very_large:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_bsort_very_large 1024 5"
	@for X in 10000000 20000000 30000000 40000000 50000000; do \
		echo -n "$$X\t";\
		/usr/bin/time -f "%E" ./bsort $$X.random a.db 2>&1; \
		rm -rf a.db; \
	done
	@echo "Done"

bench_msort_ver_large:
	@echo ""
	@echo "Sort Performance comparisons"
	@echo "Bench marking...bench_msort_ver_large 10000 5"
	@for X in 10000000 20000000 30000000 40000000 50000000; do \
		echo -n "$$X\t"; \
		/usr/bin/time -f "%E" ./msort $$X.random sorted.out 10000 5 2>&1; \
		# rm -rf a.random sorted.out; \
	done
	@echo "Done"

bench_all:
	@make clean
	@make library.o msort bsort
	@for X in 1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000 20000000 30000000 40000000 50000000; do \
		python mkrandom.py $$X.random $$X; \
	done

	@make bench_compare_msort_small
	@make bench_compare_msort_small_2
	@make bench_compare_msort_small_3
	@make bench_msort_large
	@make bench_msort_large_2
	@make bench_msort_ver_large
	@make bench_bsort_small
	@make bench_bsort_large
	@make bench_bsort_very_large

clean: 
	rm -f foo library.o foo *.test msort bsort

cleanall:
	make clean
	rm -rf *.random *.out
	rm -rf *.db