#include "library.h"
#include <math.h>

int cmpstringp(const void *a, const void *b){
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;
  return strcmp(*ia, *ib);
}

int RECORD_SIZE = 9;

void mk_runs(FILE *in_fp, FILE *out_fp, long run_length){

  //Should assert if run_length > number of total records in the file
  int numb_sorted = 0;

  // TODO : This should improve
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
RunIterator* GetRunIterator(FILE *fp, long start_pos, long run_length, 
  long buf_size){

  RunIterator* ri = (RunIterator*)malloc(sizeof(RunIterator));
  ri->data = (void*)malloc(buf_size);
  ri->fp = fp;
  ri->run_length = run_length;
  ri->cur = 0;
  ri->rec = (Record)malloc(sizeof(char) * RECORD_SIZE);
  ri->buf_size = buf_size;
  ri->cur_pos = start_pos;

  // Seek to the start_pos
  // Q : Should this be start_pos * RECORD_SIZE instead?
  fseek(fp, ri->cur_pos, SEEK_SET);
  fread(ri->data, sizeof(char), floor(buf_size/RECORD_SIZE) * RECORD_SIZE, fp);
  ri->cur_pos = ftell(fp);
  Next(ri);
  return ri;
}

Record Next(RunIterator* ri){
  if (ri->cur == ri->run_length){
    ri->rec = NULL;
    return NULL;
  } else if (ri->cur == (ri->buf_size/RECORD_SIZE)) {
    fseek(ri->fp, ri->cur_pos, SEEK_SET);
    fread(ri->data, sizeof(char), floor(ri->buf_size/RECORD_SIZE) * RECORD_SIZE, ri->fp);
    ri->cur_pos = ftell(ri->fp);
  }
  char* temp = (char*)ri->data;
  temp += RECORD_SIZE * ri->cur;
  strncpy(ri->rec, temp, RECORD_SIZE);
  ri->cur++;

  // TODO should read in more data from the disk if buf_size < sizeof(fp)
  return ri->rec;
}

// Return the miniumn from the given set of iterators
RunIterator* getMinimum(RunIterator* iterators[], int num_iterators){
  RunIterator* min = NULL;
  for (int i = 0; i < num_iterators; i++){
    if (iterators[i]->rec != NULL){
      if (min == NULL || strcmp(min->rec, iterators[i]->rec) > 0){
        min = iterators[i];
      }
    }
  }
  return min;
}

bool isDone(RunIterator* iterators[], int num_iterators){
  for (int i = 0; i < num_iterators; i++){
    if (iterators[i]->rec != NULL){
      return false;
    }
  }
  return true;
}

void merge_runs(FILE *out_fp, RunIterator* iterators[], int num_iterators, 
  long buf_size){

  Record records[num_iterators];

  while(!isDone(iterators, num_iterators)){
    int k = 0;
    for (int i = 0; i < num_iterators; i++){
      Record record = (Record)malloc(9);
      strcpy(record, getMinimum(iterators, num_iterators)->rec);
      records[k] = record;
      k++;
      Next(getMinimum(iterators, num_iterators));
    }

    for (int i = 0; i < num_iterators; i++){
      fprintf(out_fp, "%s", records[i]);
    }
  }
}
