#include "common.h"

/** 
 * Split using whitespace based on suggestion given here:
 * http://stackoverflow.com/questions/236129/splitting-a-string-in-c
 */
void word_tokenize(string s, vector<string> *tokens) {
    istringstream s_stream(s);
    copy(istream_iterator<string>(s_stream),
         istream_iterator<string>(),
         back_inserter<vector<string> >(*tokens));
};

/**
 * Splits words according to ngram segmentation
 */
void ngram_tokenize(string s, vector<string> *tokens, int n) {
    vector<string> words;
    word_tokenize(s, &words);
    string gram;
    string padding = "$$";
    n = 3;
    for(vector<string>::iterator it = words.begin();
        it != words.end();
        it ++) {
        string w = padding + (*it) + padding;
        for(int i=0; i < w.size() - n; i++) {
            gram = w.substr(i, n);
            tokens->push_back(gram);
        }
    }
}
string wordWrap(string str, size_t width) {
    size_t curWidth = width;
    while( curWidth < str.length() ) {
        string::size_type spacePos = str.rfind( ' ', curWidth );
        if( spacePos == std::string::npos )
            spacePos = str.find( ' ', curWidth );
        if( spacePos != std::string::npos ) {
            str[ spacePos ] = '\n';
            curWidth = spacePos + width + 1;
        }
    }

    return str;
}

