#include <stdio.h>
#include "library.h"
#include <time.h>
#include <fcntl.h>
#include <sys/timeb.h>

int main(int argc, char *argv[]) { 
	if (argc != 4){
		printf( "Must put <filename> <total bytes> <block size>\n" );
		return 0;
	}
	
	printf("With O_SYNC : ");
	int total_byte = atoi((argv[2]));
	int block_size =  atoi((argv[3]));
	int written_size = 0;

	char buffer[block_size];
	// Let it flush right to the disk
	int openFlags = O_CREAT | O_WRONLY | O_SYNC;

	//Open it and give owner permission!
	int fd = open(argv[1], openFlags, S_IRUSR | S_IWUSR);
	int byteWritten;
	
	struct timeb _t;
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;
	printf("( - %lu)", init);

	for (byteWritten = 0; byteWritten < total_byte; byteWritten += block_size){
		random_array(buffer, block_size);
		write(fd, buffer, block_size);
	}
	//Close the fd
	close(fd);

	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	printf(" + %lu", done);
	printf(" = %lu\n", done-init);

	printf("Without O_SYNC : ");
	FILE *file; 
	file = fopen(argv[1], "w");

	ftime(&_t);
	init = _t.time * 1000 + _t.millitm;
	printf("( - %lu)", init);
	
	byteWritten = 0;
	while (byteWritten < total_byte){
		random_array(buffer, block_size);
		fwrite(buffer, 1, block_size, file);	
		fflush(file);
		byteWritten += block_size;
	}

	ftime(&_t);
	done = _t.time * 1000 + _t.millitm;
	printf(" + %lu", done);
	printf(" = %lu\n", done-init);
	fclose(file); 
	
	return 0;
}
