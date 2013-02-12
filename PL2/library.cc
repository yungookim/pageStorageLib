#include "library.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int fixed_len_sizeof(Record *record){
	int total_byte = 0;
	for (int i = 0; i < record->size(); i++){
		total_byte += strlen(record->at(i))*sizeof(char);
	}
	return total_byte;
}

void fixed_len_write(Record *record, void *buf){
	char* byte = (char *)buf;
	for(int i = 0; i < record->size(); i++){
		for (int j = 0; j < strlen(record->at(i)); j++) {
			*(byte++) = record->at(i)[j];
		}
	}
}

void fixed_len_read(void *buf, int size, Record *record){
	char* bufptr = (char *)buf;
	int i = 0;
	int curVal = 0;
	while (i < size) {
		record->at(curVal) = strndup(bufptr+i, strlen(record->at(curVal)));
		i = i + strlen(record->at(curVal));
		curVal++;
	}
}

int var_len_sizeof(Record *record){
	int total_byte = 0;
	for (int i = 0; i < record->size(); i++){
		// strlen + 1 for the offset header
		total_byte += strlen(record->at(i))*sizeof(char) + sizeof(int);
	}
	// Total byte size plus the header size
	return total_byte;
}

void var_len_write(Record *record, void *buf){
	char* byteFields = (char *)buf;
	int* byteOffsets = (int *)buf;
				char* temp = (char *)buf;
	byteFields += sizeof(int)*record->size();

	for(int i = 0; i < record->size(); i++){
		for (int j = 0; j < strlen(record->at(i)); j++) {
			*(byteFields++) = record->at(i)[j];
		}
		*(byteOffsets++) = strlen(record->at(i));
	}
}

void var_len_read(void *buf, int size, Record *record){
	int* offsetBytes = (int *)buf;
	char* fieldBytes = (char *)buf;

	fieldBytes += sizeof(int)*record->size();

	for (int i = 0; i < record->size(); i++){
		int charSize = *(offsetBytes++); 
		record->at(i) = strndup(fieldBytes, charSize);
		*(fieldBytes += charSize);
	}
}

void init_fixed_len_page(Page *page, int page_size, int slot_size){	 
	page->page_size = page_size;
	page->slot_size = slot_size;

	page->data = malloc(page_size);

	int* header = (int*) page->data;
	// Last record size of the bytes are used for header.
	//int numb_slots = floor((page_size-sizeof(int)) / (slot_size + sizeof(int)));
        int numb_slots = fixed_len_page_capacity(page);
	
	header+=(page_size/sizeof(int))-1;
	*(header) = numb_slots;

	for (int i = 0; i < numb_slots; i++){
	// Mark all empty
		header--;
		*(header) = 0;
	}
}

int fixed_len_page_capacity(Page *page){
	return floor((page->page_size-sizeof(int)) / (page->slot_size + sizeof(int)));
}

int fixed_len_page_freeslots(Page *page){
	int* header = (int *)page->data;
        int numb_slots = fixed_len_page_capacity(page);

	// Move to end of the header
	header+=(page->page_size/sizeof(int)) - 1;
	header--;

	int count = 0;
	//printf("Header [");
	for (int i = 0; i < numb_slots; i++){
	//	printf("%d", *header);
		if (*header == 0){
			count++;
		}
		header--;
	}
//	printf("]\n");
	return count;
}

int add_fixed_len_page(Page *page, Record *r){
  int numb_slots = fixed_len_page_capacity(page);
  int* header = (int *)page->data;
	// Go to header location
	header+=page->page_size/sizeof(int) - 1;

	if (fixed_len_page_freeslots(page) == 0){
		return -1;
	}

	// Find an empty slot.
	for (int i = 0; i < numb_slots; i++){
		header--;
		if (*(header) == 0){
			// Empty slot found
			char* slot = (char *)page->data;
			slot += (page->slot_size * i);
			fixed_len_write(r, slot);
			// Change header to 1
			*(header) = 1;
			return 0;
		}
	}
}

void write_fixed_len_page(Page *page, int slot, Record *r){
	char* ptr = (char *)page->data;
	ptr = ptr + slot*page->slot_size;
	fixed_len_write(r, ptr);
	int* header  = (int *)page->data;
	header += (page->page_size/sizeof(int) - (1 + slot));
	*header = 1;
}

void read_fixed_len_page(Page *page, int slot, Record *r){
	char* _slot = (char *)page->data;
	_slot += page->slot_size * slot;
	fixed_len_read(_slot, page->slot_size, r);
}

void write_page_to_file(char* fname, Page* page){
	FILE * f;
	f = fopen(fname, "a");
	// char * buf = (char *)page->data;
	fwrite (page->data , 1 , page->page_size , f );
  fclose (f);
}