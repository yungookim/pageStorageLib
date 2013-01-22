#include <stdio.h>
#include "library.h"
#include <time.h>
#include <fcntl.h>

int main(int argc, char *argv[]) { 
	if (argc != 4){
		printf( "Must put <filename> <total bytes> <block size>\n" );
		return 0;
	}

	clock_t t1, t2;

	int total_byte = atoi((argv[2]));
	int block_size =  atoi((argv[3]));
	int written_size = 0;

	char buffer[total_byte];
	// Let it flush right to the disk
	int openFlags = O_CREAT | O_WRONLY | O_SYNC;

	//Open it and give owner permission!
	int fd = open(argv[1], openFlags, S_IRUSR | S_IWUSR);
	int byteWritten;
	t1 = clock();
	for (byteWritten = 0; byteWritten < total_byte; byteWritten += block_size){
		random_array(buffer, block_size);
		write(fd, buffer, block_size);
	}
	t2 = clock();
	//Close the fd
	close(fd);

	float diff = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
	printf("%f\n",diff);

	return 0;	
/*	FILE *file; 
	file = open(argv[1], O_SYNC);

	t1 = clock();

//	while (written_size < total_byte) {
		random_array(buffer, block_size);
		fwrite(buffer, 1, block_size, file);	
		fflush(file);
		written_size += block_size;
//	}

	fclose(file); 

	t2 = clock();

	float diff = (((float)t2 - (float)t1) / 1000000.0F ) * 1000;
	printf("%f\n",diff);
*/
	return 0; 
}
