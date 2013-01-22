#include <stdio.h>
#include "library.h"
int main(int argc, char *argv[]) { 

	long hist[26];
	long milliseconds;
	long filelen;

	FILE *file_ptr = fopen(argv[1], "r");
	int block_size = atoi(argv[2]);
	/**
	 * Compute the histogram using 2K buffers
	 */
	int ret = get_histogram( file_ptr, 
	                         hist, 
	                         block_size,
	                         &milliseconds,
	                         &filelen);

	printf("Computed the histogram in %lu ms.\n", milliseconds);
	int i;
	for(i=0; i < 26; i++) {
    		printf("%c : %lu\n", 'A' + i, hist[i]);
	}
	printf("Data rate: %f Bps\n", (double)filelen/milliseconds * 1000);
		
	printf("BLOCK SIZE %d bytes\n", block_size);
	printf("TOTAL BYTES %ld bytes\n", filelen);
	printf("TIME %lu\n", milliseconds);

	return 0; 
}
