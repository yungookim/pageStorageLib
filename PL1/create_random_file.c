#include <stdio.h>
#include "library.h"
#include <time.h>

int main(int argc, char *argv[]) { 
	if (argc != 4){
		printf( "Must put <filename> <total bytes> <block size>\n" );
		return 0;
	}

	clock_t t1, t2;

	int total_byte = atoi((argv[2]));
	int block_size =  atoi((argv[3]));
	int written_size = 0;

	char buffer[block_size];
	
	FILE *file; 
	file = fopen(argv[1],"w+");

	t1 = clock();

	while (written_size < total_byte) {
		random_array(buffer, block_size);
		fwrite(buffer, 1, block_size, file);	
		fflush(file);
		written_size += block_size;
	}

	fclose(file); 

	t2 = clock();

	float diff = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
	printf("%f\n",diff);

	return 0; 
}
