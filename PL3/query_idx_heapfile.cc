#include "library.h"
#include <sys/timeb.h>
using namespace std;

bool checkedAlready(char* str, FILE *f){
  long position = ftell(f);
  int substring_length = 5;

  char* _subsring = (char*)malloc(sizeof(char) * substring_length);
  int byteRead = fread(_subsring, sizeof(char), substring_length, f);

  while(byteRead > 0){
    if (strcmp(_subsring, str) == 0){
      return true;
    }

    free(_subsring);
    _subsring = (char*)malloc(sizeof(char) * substring_length);
    byteRead = fread(_subsring, sizeof(char), substring_length, f);
  }
  return false;
}


int main( int argc, const char* argv[] )
{
  
  bool verbose = true;
  if (argc < 5){
    printf( "Must put <index_heap_file> <start> <end> <page_size> <verbose_off(optional)>\n" );
    return 0;
  } else if (argc == 6){
    verbose = false;
  }

  const char* index_heap_file = argv[1];
  char* start = (char*)argv[2];
  char* end = (char*)argv[3];
  int page_size =  atoi((argv[4]));

  // SELECT SUBSTRING(A2, 1, 5), COUNT(*) FROM T
  // WHERE A1 >= start AND A1 <= end
  // GROUP BY SUBSTRING(A2, 1, 5) 

  //Record Start Time 
  struct timeb _t;    
  ftime(&_t);
  long init = _t.time * 1000 + _t.millitm;  


  int SLOT_SIZE = 20;
  FILE *f = fopen(index_heap_file, "r");
  Heapfile *heapfile=(Heapfile*)malloc(sizeof(Heapfile));
  heapfile->page_size=page_size;
  heapfile->file_ptr = f;

  // Prepare records
  Record cur;
  Record view;
  int NUMB_ATTRIBUTE = 2;
  for(int i = 0; i < NUMB_ATTRIBUTE; i++){
      V content = "          ";
      cur.push_back(content);
  }
  RecordIterator* iterator = (RecordIterator*)malloc(sizeof(RecordIterator));
  init_record_iterator(iterator, heapfile, SLOT_SIZE, page_size);

  int numRec = 0;
  while(iterator->hasNext){
    iterate_record(iterator); 
    read_current_record(iterator, &cur);
    // A1 = cur.at(0)
    // WHERE A1 >= start AND A1 <= end
    if (cur.at(0)[0] >= start[0] && cur.at(0)[0] <= end[0]){
      // A2 = cur.at(1)
      // Save queried to the view file
      char tmp[5];
      memcpy(tmp, &cur.at(1)[1], 5);
      view.push_back(tmp);
    }
    numRec++;
  }
  // Heap file no longer needed
  fclose(f);

  // Start Grouping and store the occurance
  int substring_length = 5;

  


  // long T_length = ftell(T);

  // rewind(T);
  
  // FILE *temp = fopen("_view", "w+");

  // int total_read = 0;
  // while (total_read < T_length){
  //   char* substring = (char*)malloc(sizeof(char) * substring_length);
  //   fread(substring, sizeof(char), substring_length, T);
  //   long cursor_position = ftell(T);
  //   // Let us count the number of occurance!
  //   rewind(T);
  //   int total_read_1 = 0;
  //   int count = 0;
  //   while (total_read_1 < T_length){
  //     char* _subsring = (char*)malloc(sizeof(char) * substring_length);
  //     fread(_subsring, sizeof(char), substring_length, T);
  //     int comp = strcmp(substring, _subsring);
  //     if (comp == 0 && !checkedAlready(substring, temp)){
  //       count++;
  //     }
  //     total_read_1 += substring_length;
  //     free(_subsring);
  //   }
  //   // Write to a temp file
  //   fwrite(&substring, sizeof(char), substring_length, temp);
    
  //   if (verbose) {
  //     printf("%s ", substring);
  //     printf("%d\n", count);  
  //   }

  //   fseek(T, cursor_position, SEEK_SET);
  //   total_read+=substring_length;
  //   free(substring);
  // }

  // fclose(temp);
  // fclose(T);


  ftime(&_t);
  long done = _t.time * 1000 + _t.millitm;
  long _time = done-init;

  printf("NUMBER OF RECORDS : %d\n", numRec);
  cout << "TIME : " << _time << " milliseconds\n";

  return 0;
}
