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
	                         2 * 1024,
	                         &milliseconds,
	                         &filelen);
		
	return 0; 
}