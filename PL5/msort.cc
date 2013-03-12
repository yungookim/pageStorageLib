#include "library.h"

int main( int argc, const char* argv[] )
{
	if (argc != 5) {
    printf( "Must put <input_file> <out_file> <mem_capacity> <k>\n");
    return 0;
  }

  char* input_file = (char*)argv[1];
  char* output_file = (char*)argv[2];
  int mem_capacity = atoi((argv[3]));
  int k = atoi((argv[4]));
  
 	int RECORD_SIZE = 9;
  FILE *in_f = fopen(input_file, "r");
  FILE *out_f = fopen(output_file, "w+");

  fseek(in_f, 0L, SEEK_END);
	int size = ftell(in_f)/RECORD_SIZE;
	fseek(in_f, 0L, SEEK_SET);

  FILE *tmp_out = fopen("t.out", "w+");

  int i = 0;
  while(i < size){
  	mk_runs(in_f, tmp_out, k);
  	i += k;
  }
  
  RunIterator* iterators[k];

  int offset = 0;
  iterators[0] = GetRunIterator(tmp_out, offset, k, RECORD_SIZE * k);
  for (int i = 1; i < k; i++){
  	iterators[i] = GetRunIterator(tmp_out, offset += RECORD_SIZE * k, k, RECORD_SIZE * k);
  }

  merge_runs(out_f, iterators, k, 100);

	return 0;
}