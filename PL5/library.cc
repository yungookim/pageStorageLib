#include "library.h"

void mk_runs(FILE *in_fp, FILE *out_fp, long run_length){
  int RECORD_SIZE = 9;
  int numb_sorted = 0;

  Record records[run_length];
  while (numb_sorted < run_length){

    Record rec;
    fread(&rec, RECORD_SIZE, 1, in_fp);

    records[numb_sorted] = rec;

    printf("%s", rec);
    numb_sorted++;
  }


  
}