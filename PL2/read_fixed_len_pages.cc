#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

int main( int argc, const char* argv[] )
{

	if (argc != 3){
		printf( "Must put <page_file> <page_size>\n" );
		return 0;
	}

	const char* page_file = argv[1];
	int page_size =  atoi((argv[2]));

    int SLOT_SIZE = 1000;
    int NUMB_ATTRIBUTE = 100;
    
    //Initialize a record(creating a schema)
    Record record;
    for(int i = 0; i < NUMB_ATTRIBUTE; i++){
        V content = "          "; 
        record.push_back(content);
    }
    //initialize a page for above records
    Page* page = (Page *)malloc(sizeof(page));
    init_fixed_len_page(page, page_size, SLOT_SIZE);
    
    //Open page_file to be read
    FILE *file;
    file = fopen(page_file, "r");
    char* pageBuf = (char *)malloc(page_size*sizeof(char));
    
    //Record Read Start time
	struct timeb _t;
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;
    int numb_pages = 0;
    while(!feof(file)){
        bzero(pageBuf, page_size);
        fread(pageBuf, sizeof(char), page_size, file);
        if(feof(file)) break; 
        
        //set page data to page buf
        page->data = pageBuf;
        for (int slot = 0; slot < fixed_len_page_capacity(page); slot++){
            //Read the page into records
            read_fixed_len_page(page, slot, &record);

            //print out this record in csv form
            for(int i = 0; i < record.size(); i++){
                if(i == record.size() - 1){
                    printf("%s\n", record.at(i));
                } else {
                    printf("%s,", record.at(i));
                }
            }
        }
        numb_pages++;
    }
	
    printf("FINISHED READING %d PAGES\n",numb_pages );
    fclose(file);

    //Record end time and compare with start time
	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long _time = done-init;

	cout << "NUMBER OF RECORDS : " << fixed_len_page_capacity(page) << "\n";
	cout << "NUMBER OF PAGES : " << numb_pages << "\n";
	cout << "TIME : " << _time << " milliseconds\n";

    return 0;
}
