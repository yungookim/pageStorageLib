#include "library.h"
#include <sys/timeb.h>

int main( int argc, const char* argv[] )
{
  
  if (argc != 5){
    printf( "Must put <heapfile> <start> <end> <page_size>\n" );
    return 0;
  }

  const char* heapfile_name = argv[1];
  char* start = (char*)argv[2];
  char* end = (char*)argv[3];
  int page_size =  atoi((argv[4]));

  // SELECT SUBSTRING(A2, 1, 5), COUNT(*) FROM T
  // WHERE A1 >= start AND A1 <= end
  // GROUP BY SUBSTRING(A2, 1, 5) 

  int SLOT_SIZE = 1000;
  FILE *f = fopen(heapfile_name, "r");
  Heapfile *heapfile=(Heapfile*)malloc(sizeof(Heapfile*));
  heapfile->page_size=page_size;
  heapfile->file_ptr = f;


  // Prepare records
  RecordIterator* iterator = (RecordIterator*)malloc(sizeof(RecordIterator*));

  init_record_iterator(iterator, heapfile, SLOT_SIZE, page_size);

  while(iterator->hasNext){

    Record cur;
    int NUMB_ATTRIBUTE = 100;
    for(int i = 0; i < NUMB_ATTRIBUTE; i++){
        V content = "          ";
        cur.push_back(content);
    }
    read_current_record(iterator, &cur);
    // A1 = cur.at(0)
    // WHERE A1 >= start AND A1 <= end
    if (cur.at(0)[0] >= start[0] && cur.at(0)[9] <= end[0]){
      // A2 = cur.at(1)
      printf("%s\n", cur.at(1));
    }

    iterate_record(iterator);
  }

  fclose(f);
  return 0;
}