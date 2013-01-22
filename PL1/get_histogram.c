#include <stdio.h>
#include "library.h"
int main(int argc, char *argv[]) { 

	/*
		int i;
		char c = 'B';
		i = (int)c;
		printf("%d\n", i);
	*/
	long hist[26];
	long milliseconds;
	long filelen;

	FILE *file_ptr = fopen("1.test", "r");
	/**
	 * Compute the histogram using 2K buffers
	 */
	int ret = get_histogram( file_ptr, 
	                         hist, 
	                         1,
	                         &milliseconds,
	                         &filelen);

	printf("1\n");
	printf("Computed the histogram in %lu ms.\n", milliseconds);
	int i;
	for(i=0; i < 26; i++) {
    	printf("%c : %lu\n", 'A' + i, hist[i]);
	}
	printf("Data rate: %f Bps\n", (double)filelen/milliseconds * 1000);
		
	return 0; 
}