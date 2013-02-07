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
		total_byte += strlen(record->at(i))*sizeof(char);
	}
	return total_byte;
}

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, void *buf){
        char  byte[fixed_len_sizeof(record)];
        int total_byte_written = 0;
	for(int i = 0; i < record->size(); i++){
                for (int j = 0; j < strlen(record->at(i)); j++) {
                    byte[total_byte_written] = record->at(i)[j];
                    total_byte_written++;
                }
        printf("total size: %d, written sofar: %d \n", fixed_len_sizeof(record), total_byte_written);
	}
	buf = byte;
        printf("sdsds %p, %p, %p,%p \n", byte + 1, &byte[0], &byte[1], buf);
 //       printf("in buf: %c, %c, %c\n", buf[0], buf[1], buf[2]);
}
