#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

/**
 * populate a random array (which is already
 * allocated with enough memory to hold n bytes.
 */
void random_array(char *array, long bytes){
	int i = 0;
	//Assume each char is 1 byte
	while (i < bytes){
		array[i] = 'A' + (rand() % 26);
		i++;
	}
}

/**
 * file_ptr : the file pointer, ready to be read from.
 * hist: an array to hold 26 long integers.  hist[0] is the
 *       number of 'A', and hist[1] is the number of 'B', etc.
 * block_size: the buffer size to be used.
 * milliseconds: time it took to complete the file scan
 * total_bytes_read: the amount data in bytes read
 *
 * returns: -1 if there is an error.
 */
 
int get_histogram(
	FILE *file_ptr,
	long hist[],
	int block_size,
	long *milliseconds,
	long *total_bytes_read) {

	struct timeb _t;

	char *buf = malloc(block_size);
	
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;

	bzero(buf, block_size);
	fread(buf, 1, block_size, file_ptr);

	while(!feof(file_ptr)) {
		int i = 0;
		while (i < block_size) {
			//printf("%d, ", buf[i]-65);
			
			hist[(int)buf[i]-65] += 1;
			i += 1;
		}
		*total_bytes_read = block_size;

		bzero(buf, block_size);
		fread(buf, 1, block_size, file_ptr);
 	}
	fclose(file_ptr);

	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long diff = done - init;
	*milliseconds = diff;
	
	//printf("time: %lu\n", *milliseconds);

	return 0;

}
