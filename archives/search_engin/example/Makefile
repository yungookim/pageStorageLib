XAPIAN_DIR = $(HOME)/Downloads/xapian-core-1.2.13

LIBS = -lxapian -luuid -lz
INC = -I $(XAPIAN_DIR)/include -L $(XAPIAN_DIR)/.libs

all: word_query word_index

.cc.o:
	g++ $(INC) -c $< 

word_query: word_query.o common.o
	g++ $(INC) -o word_query word_query.o common.o $(LIBS)

word_index: word_index.o common.o
	g++ $(INC) -o word_index word_index.o common.o $(LIBS)

clean:
	rm -f *.o word_query word_index
