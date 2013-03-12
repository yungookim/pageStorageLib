# Makefile
CC = g++ 

all: library.o foo msort
	
foo: foo.cc
	$(CC) -o $@ library.o $<

msort: msort.cc
	$(CC) -o $@ library.o $<

test_msort: 
	make clean
	make
	python mkrandom.py a.random 100
	./msort a.random sorted.out 20 10

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


clean: 
	rm -f foo library.o foo *.test msort

cleanall:
	make clean
	rm -f *.random *.out