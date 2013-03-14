#include <xapian.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, const char* argv[]) {

  if (argc < 3){
    printf( "Must put <index_name> <top-k> <keyword1> <keyword2> ...\n");
    return 1;
  }
  
  char* index_name = (char*)argv[1];
  int topk = atoi((argv[2]));

  // Build query
  vector<string> plus_terms;
  vector<string> minus_terms;
  vector<string> normal_terms;
  for (int i = 3; i < argc; i++){
    if (argv[i][0] == '+'){
      plus_terms.push_back(argv[i]);
      cout << argv[i] << " ";
    } else if (argv[i][0] == '-'){
      minus_terms.push_back(argv[i]);
    } else {
      normal_terms.push_back(argv[i]);
    }
  }

  Xapian::Query query(Xapian::Query::OP_AND_MAYBE,
    Xapian::Query(Xapian::Query::OP_AND, plus_terms.begin(), plus_terms.end()),
    Xapian::Query(Xapian::Query::OP_OR, normal_terms.begin(), normal_terms.end())
  );

  query = Xapian::Query(Xapian::Query::OP_AND_NOT,
    query,
    Xapian::Query(Xapian::Query::OP_OR, minus_terms.begin(), minus_terms.end())
  );

  Xapian::Database db(index_name);

  Xapian::Enquire enquire(db);
  enquire.set_query(query);

  Xapian::MSet matches = enquire.get_mset(0, topk); 

  for(Xapian::MSetIterator match = matches.begin(); 
    match != matches.end();
    match ++){

    Xapian::Document doc = match.get_document();

    std::string name = doc.get_value(0);
    cout << name << endl;
  }

  return 0;
}