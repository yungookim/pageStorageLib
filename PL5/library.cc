#include "library.h"

int cmpstringp(const void *a, const void *b){
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
}

int RECORD_SIZE = 9;

void mk_runs(FILE *in_fp, FILE *out_fp, long run_length){

  //Should assert if run_length > number of total records in the file
  int numb_sorted = 0;

  Record records[run_length];
  while (numb_sorted < run_length){

    Record rec = (Record)malloc(sizeof(char) * RECORD_SIZE);
    fread(rec, sizeof(char), RECORD_SIZE, in_fp);

    if(rec[RECORD_SIZE-1] == '\n'){
      rec[RECORD_SIZE-1] = '\0';
    }

    records[numb_sorted] = rec;
    numb_sorted++;
  }

  qsort(records, numb_sorted, RECORD_SIZE-1, cmpstringp);

  // Write out the sorted array
  int i = 0;
  while(i < numb_sorted){
    fprintf(out_fp, "%s\n", records[i]);
    i++;
  }
}

/**
 * creates an iterator using the `buf_size` to
 * scan through a run that starts at `start_pos`
 * with length `run_length`
 */
RecordIterator* RunIterator(FILE *fp, long start_pos, long run_length, 
  long buf_size){

  RecordIterator* ri = (RecordIterator*)malloc(sizeof(RecordIterator));
  ri->data = (void*)malloc(buf_size);
  ri->run_length = run_length;
  ri->cur = 0;
  ri->rec = (Record)malloc(sizeof(char) * RECORD_SIZE);

  // Seek to the start_pos
  // Q : Should this be start_pos * RECORD_SIZE instead?
  fseek(fp, start_pos, SEEK_SET);
  fread(ri->data, sizeof(char), RECORD_SIZE * run_length, fp);

  return ri;
}

Record Next(RecordIterator* ri){
  if (ri->cur == ri->run_length-1){
    ri->rec = NULL;
    return NULL;
  }
  
  char* temp = (char*)ri->data;
  temp += RECORD_SIZE * ri->cur;
  strncpy(ri->rec, temp, RECORD_SIZE);
  ri->cur++;
  return ri->rec;
}