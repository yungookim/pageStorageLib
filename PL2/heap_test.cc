#include "library.h"
using namespace std;

int main( int argc, const char* argv[] )
{

	Heapfile *hf = (Heapfile*)malloc(sizeof(Heapfile*));
	int page_size = 1024;
	// Truncate  file to  zero length or create a file for writing
	// READ & WRITE
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
			PageID id = alloc_page(hf);

			if (id != -1){
				write_page(page, hf, id);
			} else {
				printf("Heap Full\n");
			}
			j = 0;
			numb_pages++;
		}
	}
	
	data.close();

        Page *page1 = (Page*)malloc(sizeof(Page));
        page1->page_size = page_size;
        page1->slot_size = 1000;
        page1->data = (char*)malloc(sizeof(char)*page_size);
        read_page(hf, 1, page1);

        int SLOT_SIZE = 1000;
        int NUMB_ATTRIBUTE = 100;
        
        //Initialize a record(creating a schema)
        Record record;
        for(int i = 0; i < NUMB_ATTRIBUTE; i++){
            V content = "          "; 
            record.push_back(content);
        }

        for (int slot = 0; slot < fixed_len_page_capacity(page1); slot++){
            //Read the page into records
            read_fixed_len_page(page1, slot, &record);

            //print out this record in csv form
            for(int i = 0; i < record.size(); i++){
                if(i == record.size() - 1){
                    printf("%s\n", record.at(i));
                } else {
                    printf("%s,", record.at(i));
                }
            }
        }

	fclose(f);
	return 0;
}
