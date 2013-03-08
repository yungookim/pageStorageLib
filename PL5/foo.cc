#include "library.h"

int main( int argc, const char* argv[] )
{

	if (argc != 3) {
		printf( "Must put <input_file> <output_file>\n");
		return 0;
	}
	char* input_file = (char*)argv[1];
	char* output_file = (char*)argv[2];

	FILE *in_f = fopen(input_file, "r");
	FILE *out_f = fopen(output_file, "w+");

	mk_runs(in_f, out_f, 11);

	fclose(in_f);
	fclose(out_f);
}