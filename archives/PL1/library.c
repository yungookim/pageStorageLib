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

	int k;
	for (k = 0; k < 26; k++){
		hist[k] = 0;
	}

	struct timeb _t;

	char *buf = malloc(block_size);
	
	ftime(&_t);
	long init = _t.time * 1000 + _t.millitm;
	int i;

	while(!feof(file_ptr)) {
		bzero(buf, block_size);
		fread(buf, 1, block_size, file_ptr);
		i=0;
		while (i < block_size && buf[i] != '\0') {
			hist[(int)buf[i]-65] += 1;
			i++;
			*total_bytes_read += 1;
		}

 	}
	fclose(file_ptr);
	ftime(&_t);
	long done = _t.time * 1000 + _t.millitm;
	long diff = done - init;
	*milliseconds = diff;
	return 0;
}
