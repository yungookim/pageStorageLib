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

  if (RECORD_SIZE > mem_capacity/k){
    printf("mem_capacity is too small\n");
    return 1;
  }

  FILE *in_f = fopen(input_file, "r");
  FILE *out_f = fopen(output_file, "w+");

  fseek(in_f, 0L, SEEK_END);
	int numb_records = ftell(in_f)/RECORD_SIZE;
	fseek(in_f, 0L, SEEK_SET);

  FILE *tmp_out = fopen("t.out", "w+");
  int i = 0;
  while(i < numb_records){
  	mk_runs(in_f, tmp_out, numb_records/k);
  	i += numb_records/k;
  }
  
  RunIterator* iterators[k];

  int offset = 0;
  int eachRunSize = floor(numb_records/k);
  // int buf_sz = eachRunSize * RECORD_SIZE;
  int buf_sz = floor(mem_capacity/k);

  iterators[0] = GetRunIterator(tmp_out, offset, 
    eachRunSize, buf_sz);
  for (int i = 1; i < k; i++){
    offset += eachRunSize * RECORD_SIZE;
  	iterators[i] = GetRunIterator(tmp_out, offset, 
      eachRunSize, buf_sz);
  }

  // for (int i = 0; i < k; i++){
  //   printf("%s", iterators[i]->rec);
  //   while (Next(iterators[i]) != NULL){
  //     printf("%s", iterators[i]->rec);
  //   }
  // }

  merge_runs(out_f, iterators, k, floor(mem_capacity/k));

  fclose(in_f);
  fclose(out_f);
  fclose(tmp_out);
	return 0;
}