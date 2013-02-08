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
		total_byte += strlen(record->at(i))*sizeof(char);
	}
	return total_byte;
}

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, void *buf){
	char* byte = (char *)buf;
	for(int i = 0; i < record->size(); i++){
		for (int j = 0; j < strlen(record->at(i)); j++) {
			*(byte++) = record->at(i)[j];
		}
	}
}

/**
* Deserializes from `size` bytes from the buffer, `buf`, and
* stores the record in `record`.
*/
void fixed_len_read(void *buf, int size, Record *record){
	char* bufptr = (char *)buf;
	int i = 0;
	int curVal = 0;
	while (i < size) {
		record->at(curVal) = strndup(bufptr+i, strlen(record->at(curVal)));
		i = i + strlen(record->at(curVal));
		curVal++;
	}
	free(bufptr);
}

/**
 * Compute the number of bytes required to serialize record
 */
int var_len_sizeof(Record *record){
	int total_byte = 0;
	for (int i = 0; i < record->size(); i++){
		// strlen + 1 for the offset header
		total_byte += strlen(record->at(i))*sizeof(char) + sizeof(int);
	}
	// Total byte size plus the header size
	return total_byte;
}

/**
 * Serialize the record using variable record encoding
 */
void var_len_write(Record *record, void *buf){
	char* byteFields = (char *)buf;
	int* byteOffsets = (int *)buf;
        char* temp = (char *)buf;
	*(byteFields+=sizeof(int)*record->size());

	// Start from the back of the record because we need to find
	// the length of each record
	for(int i = 0; i < record->size(); i++){
		for (int j = 0; j < strlen(record->at(i)); j++) {
			// printf("%c", record->at(i)[j]);
			*(byteFields++) = record->at(i)[j];
		}
                *(byteOffsets++) = strlen(record->at(i));
	}
        
        //This should be removed eventually
        printf("\n\n-------printf from library.cc [");
        for(int i = 0; i < 100; i++){
            printf("%c",temp[i] );
        }
       printf("]\n\n");
}

/**
 * Deserialize the `buf` which contains the variable record encoding.
 */
void var_len_read(void *buf, int size, Record *record){
	int* offsetBytes = (int *)buf;
	char* fieldBytes = (char *)buf;

	*(fieldBytes+=sizeof(int)*record->size());

	for (int i = 0; i < record->size(); i++){
		int charSize = *(offsetBytes++); 
		record->at(i) = strndup(fieldBytes, charSize);
		*(fieldBytes += charSize);
	}
}
