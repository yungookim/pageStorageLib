#include "library.h"
#include <sys/timeb.h>
using namespace std;

int main( int argc, const char* argv[] )
{

	if (argc != 4) {
		printf( "Must put <csv_file> <heapfile> <page_size>\n");
		return 0;
	}
	const char* csv_file = argv[1];
	char* heapfile = (char*)argv[2];
	int page_size =  atoi((argv[3]));

        int SLOT_SIZE = 1000;
        int NUMB_ATTRIBUTE = 100;
	
        Heapfile *hf = (Heapfile*)malloc(sizeof(Heapfile*));
	// Truncate  file to  zero length or create a file for writing
	// READ & WRITE
	FILE *f = fopen(heapfile, "w+");

	init_heapfile(hf, page_size, f);

	Page* page = (Page *)malloc(sizeof(Page));

	// Initialize page
	init_fixed_len_page(page, page_size, SLOT_SIZE);

	// Open the csv file
	std::ifstream data(csv_file);
	std::string line;

	//Record Start Time 
	struct timeb _t;		
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;	

	int j = 0;	
	int numRec = 0;	
	int numb_pages = 0;
	while(std::getline(data,line)) {
		std::stringstream lineStream(line);
		std::string cell;

		Record record;
		while(std::getline(lineStream,cell,',')) {
			char* attribute = (char *)malloc(sizeof(cell.c_str()));
			strcpy(attribute, cell.c_str());
			record.push_back(attribute);
		}

		write_fixed_len_page(page, j++, &record);
		numRec++;
		if (j == fixed_len_page_capacity(page)){
			PageID id = alloc_page(hf);

			if (id != -1){
				write_page(page, hf, id);
			} else {
				printf("Unexpected Page ID Error\n");
			}
                        // Initialize new page
                        init_fixed_len_page(page, page_size, SLOT_SIZE);
			j = 0;
			numb_pages++;
		}
	}
        // If there is remaining page now writt yet, write the last page to file
        if(j != 0) {
            PageID id = alloc_page(hf);

            if (id != -1){
                write_page(page, hf, id);
            } else {
                printf("Unexpected Page ID Error\n");
            }
            numb_pages++;
        }

        free(page);
	data.close();
	fclose(f);

	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long _time = done-init;

	cout << "NUMBER OF RECORDS : " << numRec << "\n";
	cout << "NUMBER OF PAGES : " << numb_pages << "\n";
	cout << "TIME : " << _time << " milliseconds\n";
	return 0;
}
