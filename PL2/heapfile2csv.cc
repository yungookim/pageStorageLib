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

	if (argc != 4){
		printf( "Must put <csv_file> <heapfile> <page_size>\n" );
		return 0;
	}

	const char* csv_file = argv[1];
    const char* heapfile = argv[2];
    int page_size =  atoi((argv[3]));

    int SLOT_SIZE = 1000;
    int NUMB_ATTRIBUTE = 100;

    //Open csv_file to be written
    FILE *cfile = fopen(csv_file, "w");

    //Open heapfile to be read
    FILE *file;
    file = fopen(heapfile, "r+");
    Heapfile *hf = (Heapfile*)malloc(sizeof(Heapfile));
    hf->file_ptr = file;
    hf->page_size = page_size;

    //Record Read Start time
    struct timeb _t;
    ftime(&_t);
    long init = _t.time * 1000 + _t.millitm;
    int pid = 0;
    int numRec = 0;
    while(true){
        Record record;
        for(int i = 0; i < NUMB_ATTRIBUTE; i++){
            V content = "          "; 
            record.push_back(content);
        }
        //initialize a page for above records
        Page* page = (Page *)malloc(sizeof(page));
        init_fixed_len_page(page, page_size, SLOT_SIZE);
        read_page(hf, pid, page);
        
        // If page->data is eof, get out of the loop
        if(!*(char *)page->data) break;
        for (int slot = 0; slot < fixed_len_page_capacity(page) &&
                *((char *)page->data + page->slot_size*slot); slot++){
            //Read the page into records
            read_fixed_len_page(page, slot, &record);
            numRec++;
            //print out this record in csv form
            for(int i = 0; i < record.size(); i++){
                if(i == record.size() - 1){
                    fprintf(cfile, "%s\n", record.at(i));
                } else {
                    fprintf(cfile, "%s,", record.at(i));
                }
            }
        }
        pid++;
    }
    fclose(cfile);
    fclose(file);

    //Record end time and compare with start time
	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long _time = done-init;

	cout << "NUMBER OF RECORDS WRITTEN: " << numRec << "\n";
	cout << "NUMBER OF PAGES WRITTEN: " << pid << "\n";
	cout << "TIME : " << _time << " milliseconds\n";

    return 0;
}
