#include <xapian.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include "common.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cerr << "Usage: <idxname>" << endl;
        exit(0);
    }

    char *idxname = argv[1];
    Xapian::WritableDatabase db(idxname, Xapian::DB_CREATE_OR_OPEN);
    Xapian::Document doc;

    vector<string> words;
    words.push_back("hello world again and again");
    words.push_back("a brave new world world");

    long lineno = 0;
    for(vector<string>::iterator it = words.begin(); it != words.end(); it++, lineno++) {
        cout << "line " << lineno << ": ";
        string &s = *it;

        // perform tokenization
        vector<string> tokens;
        word_tokenize(s, &tokens);

        // populate the document
        // value[0] will be the original line
        doc.clear_terms();
        doc.clear_values();
        doc.add_value(0, string(s));
        // document is the bag of terms
        for(vector<string>::iterator it_token=tokens.begin(); 
            it_token != tokens.end(); 
            it_token++) {
            string &token = *it_token;
            cout << token << " ";
            doc.add_term(token);
        }
        cout << endl;
        db.add_document(doc);
        if(lineno % 1000 == 0) {
            db.commit();
        }
    }
}
