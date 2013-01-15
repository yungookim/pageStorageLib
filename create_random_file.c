#include <stdio.h> 

int main(int argc, char *argv[]) { 
	if (argc != 4){
		printf( "Must put <filename> <total bytes> <block size>\n" );
		return 0;
	}

	FILE *file; 
	file = fopen(argv[1],"w+");

	int total_byte = atoi((argv[2]));
	int block_size =  atoi((argv[3]));
	int written_size = 0;

	char buffer[block_size];
	
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

	fclose(file); /*done!*/ 
	return 0; 
}
