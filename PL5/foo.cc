#include "library.h"

int main( int argc, const char* argv[] )
{

  if (argc != 4) {
    printf( "Must put <input_file> <output_file> <RUN_LENGTH>\n");
    return 0;
  }
  char* input_file = (char*)argv[1];
  char* output_file = (char*)argv[2];
  int RUN_LENGTH = atoi((argv[3]));

  FILE *in_f = fopen(input_file, "r");
  FILE *out_f = fopen(output_file, "w+");

  // Sort run
  mk_runs(in_f, out_f, RUN_LENGTH);

  int RECORD_SIZE = 9;

  //out_f is already n-sorted
  RecordIterator* ri = RunIterator(out_f, 0, RUN_LENGTH, RECORD_SIZE * RUN_LENGTH);

  while (ri->rec != NULL){
    Next(ri);
    cout << ri->rec;
  }

  free(ri);
  fclose(in_f);
  fclose(out_f);
}