#include <stdio.h> 
#include <time.h>

int main(int argc, char *argv[]) { 
	if (argc != 4){
		printf( "Must put <filename> <total bytes> <block size>\n" );
		return 0;
	}

	clock_t t1, t2;

	FILE *file; 
	file = fopen(argv[1],"w+");

	int total_byte = atoi((argv[2]));
	int block_size =  atoi((argv[3]));
	int written_size = 0;

	char buffer[block_size];
	
	t1 = clock();
	while (written_size < total_byte) {
		int written = 0;
		while (written < block_size){
			char ch = 'a' + rand() % (('z'-'a') + 1);
			fprintf(file,"%c", ch);
			written++;
		}
		fflush(file);
		written_size += block_size;
	}
	t2 = clock();
	float diff = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
    printf("%f\n",diff);
    

	fclose(file); /*done!*/ 
	return 0; 
}
