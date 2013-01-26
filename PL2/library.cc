#include "library.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Compute the number of bytes required to serialize record
 */
int fixed_len_sizeof(Record *record){
	int total_byte = 0;
	for (int i = 0; i < record->size(); i++){
		//char = 1 byte
		total_byte += strlen(record->at(i));
	}
	return total_byte;
}

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, void *buf){
	unsigned char* arr;
    	for(int i = 0; i < record->size(); i++) {
		arr[i] = static_cast<unsigned char>(record->at(0)[i]);
	}
	buf = &arr;
}
