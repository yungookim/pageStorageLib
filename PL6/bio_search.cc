#include <xapian.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/timeb.h>
using namespace std;

int main(int argc, const char* argv[]) {

  if (argc < 3){
    printf( "Must put <index_name> <top-k> <keyword1> <keyword2> ...\n");
    return 1;
  }
  
  char* index_name = (char*)argv[1];
  int topk = atoi((argv[2]));

  Xapian::Query query;

  //Record Start Time 
  struct timeb _t;    
  ftime(&_t);
  long init = _t.time * 1000 + _t.millitm; 

  // Build query
  std::string arg;
  for (int i = 3; i < argc; i++){
    arg = argv[i];
    if (argv[i][0] == '+'){
      query = Xapian::Query(Xapian::Query::OP_AND, query, Xapian::Query(arg.substr(1, sizeof(argv[i])-1)));
    } else if (argv[i][0] == '-'){
      query = Xapian::Query(Xapian::Query::OP_AND_NOT, query, Xapian::Query(arg.substr(1, sizeof(argv[i])-1)));
    } else {
      query = Xapian::Query(Xapian::Query::OP_OR, query, Xapian::Query(argv[i]));
    }
  }

  Xapian::Database db(index_name);

  Xapian::Enquire enquire(db);
  enquire.set_query(query);

  Xapian::MSet matches = enquire.get_mset(0, topk); 

  for(Xapian::MSetIterator match = matches.begin(); 
    match != matches.end();
    match ++){

    Xapian::Document doc = match.get_document();

    std::string name = doc.get_value(0);
    std::string bio = doc.get_value(1);
    cout << name << endl;
    cout << bio << endl;
  }

  ftime(&_t);
  long done = _t.time * 1000 + _t.millitm;
  long _time = done-init;
  cerr << _time;

  return 0;
}