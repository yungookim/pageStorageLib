#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

typedef char* Record;

typedef struct {
  FILE *fp;
  int cur;
  long run_length;
  Record rec;
  void *data;
} RecordIterator;

/**
 * creates runs of length `run_length` in the `out_fp`.
 */
void mk_runs(FILE *in_fp, FILE *out_fp, long run_length); 

/**
 * creates an iterator using the `buf_size` to
 * scan through a run that starts at `start_pos`
 * with length `run_length`
 */
RecordIterator* RunIterator(FILE *fp, long start_pos, long run_length, 
	long buf_size);

/**
 * reads the next record.  Returns null if
 * iterator reads the end of the run.
 */
Record Next(RecordIterator* ri);