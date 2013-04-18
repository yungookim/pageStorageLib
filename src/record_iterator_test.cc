#include "library.h"

int main( int argc, const char* argv[] )
{

	int PAGE_SIZE = 10000;
	int SLOT_SIZE = 1000;
	FILE *f = fopen("heap_directory", "r");
	Heapfile *heapfile=(Heapfile*)malloc(sizeof(Heapfile*));
	heapfile->page_size=PAGE_SIZE;
	heapfile->file_ptr = f;


	// Prepare records
	RecordIterator* iterator = (RecordIterator*)malloc(sizeof(RecordIterator*));

	init_record_iterator(iterator, heapfile, SLOT_SIZE, PAGE_SIZE);

	while(iterator->hasNext){

		Record cur;
	  int NUMB_ATTRIBUTE = 100;
	  for(int i = 0; i < NUMB_ATTRIBUTE; i++){
	      V content = "          ";
	      cur.push_back(content);
	  }
	  read_current_record(iterator, &cur);
	  for(int i = 0; i < NUMB_ATTRIBUTE; i++){
	      printf("%s,", cur.at(i));
	  }
	  printf("\n");
	  iterate_record(iterator);
  }
  

	fclose(f);
	return 0;
}