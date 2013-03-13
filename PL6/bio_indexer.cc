#include <xapian.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
<<<<<<< HEAD
<<<<<<< HEAD
#include "xapian.h"
=======
#include <xapian.h>
>>>>>>> .
=======
>>>>>>> c9560a6544936adfc69859a1678ae461c9a225e0
using namespace std;
// using namespace Xapian;

int main(int argc, const char* argv[]) {

	if (argc != 3) {
		printf( "Must put <parsed_biographies> <index_name>\n");
		return 0;
	}

	char* parsed_biographies = (char*)argv[1];
	char* index_name = (char*)argv[2];

	std::ifstream data(parsed_biographies);
	std::string name;
	std::string bio;

	Xapian::WritableDatabase db(index_name, Xapian::DB_CREATE_OR_OPEN);
	Xapian::Document doc;
	int lineno = 0;
	while(std::getline(data,name)) {
		std::getline(data,bio);
		std::stringstream lineStream(bio);
		// cout << name;
		// cout << bio;
		std::string term;
		while(std::getline(lineStream,term,' ')){
			cout << term;
		}

		doc.add_value(0, name);
		doc.add_value(1, bio);

		db.add_document(doc);
		doc.clear_terms();
		doc.clear_values();
		lineno++;
		if(lineno % 1000 == 0) {
 	   db.commit();
    }
	}
	return 0;
}
