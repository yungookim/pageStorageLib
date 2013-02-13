#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <fstream>
#include <iostream>
using namespace std;

int main( int argc, const char* argv[] )
{
	if (argc != 3){
		printf( "Must put <page_file> <page_size>\n" );
		return 0;
	}

	char* page_file = (char*)argv[1];
	int page_size =  atoi((argv[2]));

	void* buf = malloc(page_size);

	// cout << buf;

	int SLOT_SIZE = 1000;
	int numb_slots = (page_size-sizeof(int)) / (SLOT_SIZE + sizeof(int));

	int* header = (int*)buf;
	header+=page_size/sizeof(int)-1;

	ifstream f(page_file);
	// f.read((char*)buf, page_size);

	// //Get length of the file
	// f.seekg (0, ios::end);
	// int length = f.tellg();
	// f.seekg (0, ios::beg);

	// char* data = (char*)buf;
	// while (f.tellg() < length){
	// 	int counter = 0;
	// 	while (counter < numb_slots){
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		cout << *(data++);
	// 		counter+=10;
	// 		cout << ",";
	// 	}
	// 	f.seekg(page_size + counter);
	// }
	// cout << numb_slots << "\n";

	FILE *stream = fopen(page_file,"r");
	int bytesRead;
  
	while (bytesRead = fread((char*)buf, 1, page_size, stream)){
		char* data = (char*)buf;
		int count = 0;
		while (count < page_size){
			for (int k = 0; k < SLOT_SIZE/10; k++){
				for (int i = 0; i < 10; i++){
					cout << *data++;
					count++;
				}
				cout << ",";
			}
			cout << "\n";
		}
	}
	return 0;
}