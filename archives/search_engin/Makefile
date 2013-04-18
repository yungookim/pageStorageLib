# Makefile
CC = g++ 
INCLUDE=-I ./include -L ./.libs
LIBS=-lxapian -lz 

all: bio_indexer bio_search

bio_indexer: bio_indexer.cc
	$(CC) $(INCLUDE) -o $@ $< $(LIBS)

bio_search: bio_search.cc
	$(CC) $(INCLUDE) -o $@ $< $(LIBS)

create_lists:
	@for X in 1000 2500 5000 10000 20000 31918 47877 63836 79795 95754 111713 127672 143631; do \
		head -n $$X biographies.parsed.list > $$X.list; \
	done

bench_indexer:
	#original filne lines = 159594
	#bench_indexer running...
	@echo "FileSize(numbLine)\tTime" 1>&2
	@for X in 1000 2500 5000 10000 20000 31918 47877 63836 79795 95754 111713 127672 143631; do \
		echo -n "$$X\t" 1>&2 ; \
		/usr/bin/time -f "%E" ./bio_indexer $$X.list $$X.index; \
	done
	echo -n "159594\t" 1>&2 ; \
	/usr/bin/time -f "%E" ./bio_indexer biographies.parsed.list 159594.index; \
	#done

bench_searches:
	@for X in 1000 2500 5000 10000 20000 31918 47877 63836 79795 95754 111713 127672 143631 159594; do \
		echo -n "$$X\t" 1>&2; \
		./bio_search $$X.index 20 $(TERMS); \
		echo "" 1>&2; \
	done

bench_search:
	@echo "10 OR-keywords" 1>&2
	@make bench_searches TERMS="richard carolinas managed possessed years challenges hiatus ahead died same"
	@echo "5 AND-keywords and 5 OR-keywords" 1>&2
	@make bench_searches TERMS="richard carolinas +is +and possessed +years challenges hiatus ahead died +same"
	@echo "5 NOT-keywords and 5 OR-keywords" 1>&2
	@make bench_searches TERMS="-richard carolinas is and -possessed -years -challenges -hiatus ahead died same"
	@echo "2 NOT-keywords, 3 AND-keywords and 5 OR-keywords" 1>&2
	@make bench_searches TERMS="-richard carolinas is and -possessed +years +challenges +hiatus ahead died -same"
	@echo "5 NOT-keywords, 4 AND-keywords and 1 OR-keywords" 1>&2
	@make bench_searches TERMS="-richard -carolinas +and -possessed +years +challenges +hiatus -ahead -died -same"

clean: 
	rm -rf bio_indexer bio_search
