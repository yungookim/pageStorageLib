#include "library.h"
#include <sys/timeb.h>
using namespace std;

int main( int argc, const char* argv[] )
{
  bool verbose = true;
  if (argc < 5){
    printf( "Must put <heapfile> <start> <end> <page_size> <verbose_off(optional)>\n" );
    return 0;
  } else if (argc == 6){
    verbose = false;
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
  Heapfile *heapfile=(Heapfile*)malloc(sizeof(Heapfile));
  heapfile->page_size=page_size;
  heapfile->file_ptr = f;

  //Record Start Time 
  struct timeb _t;    
  ftime(&_t);
  long init = _t.time * 1000 + _t.millitm;  

  // Prepare records
  RecordIterator* iterator = (RecordIterator*)malloc(sizeof(RecordIterator));
  Record cur;
  Record view;
  int NUMB_ATTRIBUTE = 100;
  for(int i = 0; i < NUMB_ATTRIBUTE; i++){
    V content = "          ";
    cur.push_back(content);
  }

  init_record_iterator(iterator, heapfile, SLOT_SIZE, page_size);

  int numRec = 0;
  int numRecS = 0;
  while(iterator->hasNext){
    iterate_record(iterator); 
    read_current_record(iterator, &cur);
    // A1 = cur.at(0)
    // WHERE A1 >= start AND A1 <= end
    if (cur.at(0)[0] >= start[0] && cur.at(0)[0] <= end[0]){
      // A2 = cur.at(1)
      char* tmp = (char*)malloc(sizeof(char) * 5);
      memcpy(tmp, &cur.at(1)[1], 5);
      view.push_back(tmp);
    }
    numRec++;
  }
  // Heap file no longer needed
  fclose(f);

  // Start Grouping and store the occurance
  for ( int i = 0; i< view.size(); i++){
      int counter = 1;
      int k = i + 1;
      while (k < view.size()){
          if (strcmp(view.at(i), view.at(k)) == 0){
                counter++;
                view.erase(view.begin() + k); 
            } else {
                k++;
            }
        }
      numRecS++;
      if (verbose) {
          printf("%s ", view.at(i));
          printf("%d\n", counter);
        }
    }

  ftime(&_t);
  long done = _t.time * 1000 + _t.millitm;
  long _time = done-init;

  printf("NUMBER OF RECORDS : %d\n", numRec);
  printf("NUMBER OF RECORDS SELECTED: %d\n", numRecS);
  cout << "TIME : " << _time << " milliseconds\n";

  return 0;
}
