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
  RunIterator* ri = GetRunIterator(out_f, 0, RUN_LENGTH, RECORD_SIZE * RUN_LENGTH);

  while (ri->rec != NULL){
    // cout << ri->rec;
    Next(ri);
  }
  free(ri);
  fclose(in_f);
  fclose(out_f);

  FILE *r1 = fopen("1.random", "r");
  FILE *r2 = fopen("2.random", "r");
  FILE *r3 = fopen("3.random", "r");
  FILE *r4 = fopen("4.random", "r");
  FILE *r5 = fopen("5.random", "r");

  FILE *out = fopen("1.out", "w+");

  mk_runs(r1, out, 5);
  mk_runs(r2, out, 5);
  mk_runs(r3, out, 5);
  mk_runs(r4, out, 5);
  mk_runs(r5, out, 5);

  int offset = 0;
  RunIterator* iterators[5];
  iterators[0] = GetRunIterator(out, offset, 5, RECORD_SIZE * 5);
  iterators[1] = GetRunIterator(out, offset += RECORD_SIZE * 5, 5, RECORD_SIZE * 5);
  iterators[2] = GetRunIterator(out, offset += RECORD_SIZE * 5, 5, RECORD_SIZE * 5);
  iterators[3] = GetRunIterator(out, offset += RECORD_SIZE * 5, 5, RECORD_SIZE * 5);
  iterators[4] = GetRunIterator(out, offset += RECORD_SIZE * 5, 5, RECORD_SIZE * 5);


  FILE *final_out = fopen("final.out", "w+");
  merge_runs(final_out, iterators, 5, 100);


  fclose(r1);
  fclose(r2);
  fclose(r3);
  fclose(r4);
  fclose(r5);
  fclose(out);
  fclose(final_out);
}