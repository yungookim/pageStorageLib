#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main( int argc, const char* argv[] )
{

	if (argc != 4){
		printf( "Must put <csv_file> <page_file> <page_size>\n" );
		return 0;
	}

	const char* csv_file = argv[1];
	char* page_file = (char*)argv[2];
	int page_size =  atoi((argv[3]));

	Page* page = (Page *)malloc(sizeof(Page));

	// Initialize page
	init_fixed_len_page(page, page_size, 1000);

	// Open the csv file

	ifstream infile;
	char token[10] ;
	infile.open (csv_file, ifstream::in);
	int j = 0;
	if (infile.is_open()) {
		while (infile.good()) {
			Record record;
			// Assume 100 Attributes
			for (int i = 0; i < 100; i++){
				infile.getline(token, 254, ',');
				for (int k = 0; k < 10; k++){
					record.push_back(token[k]);
				}
			}
			// add_fixed_len_page(page, &record);

			write_fixed_len_page(page, j++, &record);

			if (j == fixed_len_page_capacity(page)){
				write_page_to_file(page_file, page);
				j = 0;
			}
		}
		infile.close();
		free(page);
	} else {
		cout << "Error opening file";
	}
  return 0;
}