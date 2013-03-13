#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

void word_tokenize(string s, vector<string> *tokens);
void ngram_tokenize(string s, vector<string> *tokens, int n);
string wordWrap(string str, size_t width=55);
