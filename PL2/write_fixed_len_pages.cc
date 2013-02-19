#include "library.h"
#include <time.h>
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

	Page* page = (Page *)malloc(sizeof(Page));

	// Initialize page
	init_fixed_len_page(page, page_size, 1000);
				
	// Open the csv file
	std::ifstream data(csv_file);
	std::string line;

	//Record Start Time 
	struct timeb _t;		
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;
	
	int j = 0;		
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
		if (j == fixed_len_page_capacity(page)){
			write_page_to_file(page_file, page);
			j = 0;
			numb_pages++;
		}
	}
	
	data.close();
	free(page);

	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long _time = done-init;

	cout << "NUMBER OF RECORDS : " << fixed_len_page_capacity(page) << "\n";
	cout << "NUMBER OF PAGES : " << numb_pages << "\n";
	cout << "TIME : " << _time << " milliseconds\n";
	return 0;
}
