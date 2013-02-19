#include "library.h"
using namespace std;

int main( int argc, const char* argv[] )
{

	Heapfile *hf = (Heapfile*)malloc(sizeof(Heapfile*));
	int page_size = 1024;
	// Truncate  file  to  zero length or create a file for writing
	FILE *f = fopen("heap_directory", "w+");

	init_heapfile(hf, page_size, f);

	const char* csv_file = "random";

	Page* page = (Page *)malloc(sizeof(Page));

	// Initialize page
	init_fixed_len_page(page, page_size, 1000);
				
	// Open the csv file
	std::ifstream data(csv_file);
	std::string line;

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
			
			write_page(page, hf, alloc_page(hf));

			j = 0;
			numb_pages++;
		}
	}
	
	data.close();

	fclose(f);
	return 0;
}