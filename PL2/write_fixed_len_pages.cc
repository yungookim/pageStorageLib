#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
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

	std::ifstream data(csv_file);

	std::string line;
	while(std::getline(data,line)) {
		std::stringstream lineStream(line);
		std::string cell;

		Record record;
		while(std::getline(lineStream,cell,',')) {
			record.push_back(cell.c_str());
			cout << cell << " ";
		}
		add_fixed_len_page(page, &record);
	}

	// char* c = (char*)page->data;
	// for (int i = 0; i < 10000; i++){
	// 	printf("%c", *c);
	// 	c++;
	// }


	write_page_to_file(page_file, page);
	data.close();
	free(page);

	// if (infile.is_open()) {
	// 	while (infile.good()) {
	// 		Record record;
	// 		// Assume 100 Attributes
	// 		for (int i = 0; i < 100; i++){
	// 			infile.getline(token, 1100, ',');
	// 			record.push_back(token);
	// 			printf(token);
	// 			printf("-%d ", i);
	// 		}
	// 		printf("\n");
	// 		add_fixed_len_page(page, &record);
	// 	}
	// 	write_page_to_file(page_file, page);
	// 	infile.close();
	// 	free(page);
	// } else {
	// 	cout << "Error opening file";
	// }
  return 0;
}