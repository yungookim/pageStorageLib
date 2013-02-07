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
	unsigned char byte[record->size()];
	for(int i = 0; i < record->size(); i++){
		byte[i] = *((unsigned char*) record->at(i));
	}
	buf = &byte;
}

/**
 * Deserializes from `size` bytes from the buffer, `buf`, and
 * stores the record in `record`.
 */
void fixed_len_read(void *buf, int size, Record *record){	
	for (int i = 0; i < 11; i++){
		buf[i]
	}
}
