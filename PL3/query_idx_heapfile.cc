#include "library.h"
#include <sys/timeb.h>
using namespace std;

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
/*
  Record checked;
  bool isChecked = false;
  for (int i = 0; i < view.size(); i++){
    int counter = 0;
    isChecked = false;
    for (int j = 0; j < checked.size(); j++){
      if (strcmp(checked.at(j),view.at(i)) == 0){
        isChecked = true;
      }
    }

    if (!isChecked){
      for (int k = 0; k < view.size(); k++){
        if (strcmp(view.at(i), view.at(k)) == 0){
          counter++;
        }
      }
      checked.push_back(view.at(i));
      if (verbose) {
        printf("%s ", view.at(i));
        printf("%d\n", counter);  
      }  
    }
  }
*/
  ftime(&_t);
  long done = _t.time * 1000 + _t.millitm;
  long _time = done-init;

  printf("NUMBER OF RECORDS : %d\n", numRec);
  printf("NUMBER OF RECORDS SELECTED: %d\n", numRecS);
  cout << "TIME : " << _time << " milliseconds\n";

  return 0;
}
