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
  int cur_pos;
  int buf_size;
  long run_length;
  Record rec;
  void *data;
} RunIterator;

/**
 * creates runs of length `run_length` in the `out_fp`.
 */
void mk_runs(FILE *in_fp, FILE *out_fp, long run_length); 

/**
 * creates an iterator using the `buf_size` to
 * scan through a run that starts at `start_pos`
 * with length `run_length`
 */
RunIterator* GetRunIterator(FILE *fp, long start_pos, long run_length, 
	long buf_size);

/**
 * reads the next record.  Returns null if
 * iterator reads the end of the run.
 */
Record Next(RunIterator* ri);

/**
 * merges the iterators using long buf_size, 
 * and writes the result to FILE *out_fp. 
 * This will create longer runs in FILE *out_fp.
 * Note : buf_size given here resembles the buf_size
 * allowed by the sorted buffer not for the entire sorting.
 */
void merge_runs(FILE *out_fp, RunIterator* iterators[], int num_iterators, 
	long buf_size);	
