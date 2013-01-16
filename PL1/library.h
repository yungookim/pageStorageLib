#include <stdio.h>
/**
 * populate a random array (which is already
 * allocated with enough memory to hold n bytes.
 */
void random_array(char *array, long bytes);

int get_histogram(
	FILE *file_ptr,
	long hist[],
	int block_size,
	long *milliseconds,
	long *total_bytes_read);