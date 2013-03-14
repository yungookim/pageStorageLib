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

  vector<string> terms;

  std::string keywords[argc-2];
  for (int i = 2; i < argc; i++){
  	keywords[i-2] = argv[i];

  	// HACK
  	terms.push_back(argv[i]);
  }

  Xapian::Database db(index_name);

  Xapian::Query query(
    Xapian::Query::OP_OR,
    terms.begin(),
    terms.end()
	);

	Xapian::Enquire enquire(db);
	enquire.set_query(query);

	Xapian::MSet matches = enquire.get_mset(0, topk); 

	for(Xapian::MSetIterator match = matches.begin(); 
		match != matches.end();
		match ++){

		Xapian::Document doc = match.get_document();

		std::string value0 = doc.get_value(0);
		cout << value0 << endl;
	}

	return 0;
}