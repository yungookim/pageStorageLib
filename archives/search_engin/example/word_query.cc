#include <xapian.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc < 3) {
        cerr << "Usage: <idxname> <query string>" << endl;
        exit(1);
    }

    Xapian::Database db(argv[1]);
    Xapian::Enquire enquire(db);

    string query_string(argv[2]);
    vector<string> query_terms;

    word_tokenize(query_string, &query_terms);
    Xapian::Query query(Xapian::Query::OP_OR,
    	query_terms.begin(),
    	query_terms.end());

    cout << "Searching: " << query.get_description() << endl;

    enquire.set_query(query);
    Xapian::MSet matches = enquire.get_mset(0, 10);

    cout << matches.size() << " results found." << endl;

    for(Xapian::MSetIterator i = matches.begin(); i != matches.end(); i++) {
    	Xapian::Document doc = i.get_document();
    	cout << doc.get_value(0) << endl;
    }
}
