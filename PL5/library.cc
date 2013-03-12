#include "library.h"
#include <assert.h>

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
  // reduce the buffer size down to the factor of the record size
  ri->buf_size = floor(buf_size/RECORD_SIZE) * RECORD_SIZE;
  // printf("buf size %ld\n", ri->buf_size);
  ri->data = (void*)malloc(ri->buf_size);
  ri->fp = fp;
  ri->run_length = run_length;
  ri->cur = 0;
  ri->read = 0;

  // Seek to the start_pos
  // Q : Should this be start_pos * RECORD_SIZE instead?
  fseek(fp, start_pos, SEEK_SET);
  fread(ri->data, sizeof(char), ri->buf_size, fp);
  ri->cur_file_pos = ftell(fp);
  Next(ri);
  return ri;
}

Record Next(RunIterator* ri){
  if (ri->cur == ri->run_length){
    ri->rec = NULL;
    return NULL;
  } else if (ri->read == ri->buf_size){
    // Read in the next batch
    // printf("CUR BATCH %ld\n", ftell(ri->fp));
    ri->read = 0;
    ri->data = (void*)malloc(ri->buf_size);
    fseek(ri->fp, ri->cur_file_pos, SEEK_SET);
    fread(ri->data, sizeof(char), ri->buf_size, ri->fp);
    ri->cur_file_pos = ftell(ri->fp);
    // printf("NEXT BATCH %ld\n", ftell(ri->fp));
  }

  char* temp = (char*)ri->data;
  temp += ri->read;
  // printf("%s\n", temp);
  free(ri->rec);
  ri->rec = (Record)calloc(sizeof(char), RECORD_SIZE);
  strncpy(ri->rec, temp, RECORD_SIZE);
  ri->cur++;
  ri->read += RECORD_SIZE;
  // printf("\n%lu, %s-\n", sizeof(ri->rec), ri->rec);
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
  // Enforce the buffer size
  // assert(num_iterators*9 <= buf_size);

  while(!isDone(iterators, num_iterators)){
    int k = 0;
    for (int i = 0; i < num_iterators; i++){
      Record record = (Record)malloc(9);
      RunIterator* tmp = getMinimum(iterators, num_iterators);
      strcpy(record, tmp->rec);
      records[k] = record;
      k++;
      Next(tmp);
    }

    for (int i = 0; i < num_iterators; i++){
      fprintf(out_fp, "%s", records[i]);
    }
  }
}
