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
	char* value; 
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
		total_byte += strlen(record->at(i))*sizeof(char) + 1;
	}
	// Total byte size plus the header size
	return total_byte;
}

/**
 * Serialize the record using variable record encoding
 */
void var_len_write(Record *record, void *buf){
	char* byteFields = (char *)buf;
	char* byteOffsets = (char *)buf;

	for (int i = 0 ; i < record->size() ; i++){
		*(byteFields+=sizeof(int));
	}	

	// Start from the back of the record because we need to find
	// the length of each record
	for(int i = 0; i < record->size(); i++){
		int counter = 0;
		for (int j = 0; j < strlen(record->at(i)); j++) {
			printf("%c", record->at(i)[j]);

			*(byteFields++) = record->at(i)[j];
			counter++;
		}
		*(byteOffsets+=sizeof(int)) = counter;
	}
}

/**
 * Deserialize the `buf` which contains the variable record encoding.
 */
void var_len_read(void *buf, int size, Record *record){
	char* offsetBytes = (char *)buf;
	char* fieldBytes = (char *)buf;

	for (int i = 0; i < record->size(); i++){
		*(fieldBytes++);
	}

	for (int i = 0; i < record->size(); i++){
		int charSize = *(offsetBytes++);
		record->at(i) = strndup(fieldBytes, charSize);
		*(fieldBytes += charSize);
	}
}
