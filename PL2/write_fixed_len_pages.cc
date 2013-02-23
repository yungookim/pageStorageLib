#include "library.h"
#include <sys/timeb.h>
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

        int SLOT_SIZE = 1000;
        int NUMB_ATTRIBUTE = 100;
	
        Page* page = (Page *)malloc(sizeof(Page));

	// Initialize page
	init_fixed_len_page(page, page_size, SLOT_SIZE);
	
        //Initialize a record(creating a schema)
        Record record;
        for(int i = 0; i < NUMB_ATTRIBUTE; i++){
            V content = "          "; 
            record.push_back(content);
        }

	// Open the csv file
	std::ifstream data(csv_file);
	std::string line;

	//Record Start Time 
	struct timeb _t;		
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;
	
	int j = 0;		
	int numb_pages = 0;
        int numb_records = 0;
        int firstRecord = 1;
	while(std::getline(data,line)) {
		std::stringstream lineStream(line);
		std::string cell;

                int field = 0;
		while(std::getline(lineStream,cell,',')) {
			char* attribute = (char *)malloc(strlen(cell.c_str()));
			strcpy(attribute, cell.c_str());
			//record.push_back(attribute);
                        record.at(field) = attribute;
                        field++;
		} 
		write_fixed_len_page(page, j++, &record);
                numb_records++;
                // If page is full, write to file.
                if (j == fixed_len_page_capacity(page)){
                    write_page_to_file(page_file, page);
                    // Initialize new page
                    init_fixed_len_page(page, page_size, SLOT_SIZE);
                    j = 0;
                    numb_pages++;
                }
	}
        // If there is remaining page now written to file yet, write the last page to file
        if(j != 0) {
            write_page_to_file(page_file, page);
            numb_pages++;
        }
	
	data.close();
	free(page);

	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long _time = done-init;

	cout << "NUMBER OF RECORDS : " << numb_records << "\n";
	cout << "NUMBER OF PAGES : " << numb_pages << "\n";
	cout << "TIME : " << _time << " milliseconds\n";
	return 0;
}
