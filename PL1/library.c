#include "library.h"

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
