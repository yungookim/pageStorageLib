#include "library.h"

using namespace std;

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
    int* header  = (int *)page->data;

    ptr = ptr + slot*page->slot_size;
    header += page->page_size/sizeof(int) - 1;
    fixed_len_write(r, ptr);
    header--;
    *(header - slot) = 1;
}

void read_fixed_len_page(Page *page, int slot, Record *r){
    char* _slot = (char *)page->data;	
    _slot += page->slot_size * slot;
    fixed_len_read(_slot, page->slot_size, r);
}

void write_page_to_file(char* fname, Page* page){
    FILE * f;
    f = fopen(fname, "a");
    char* buf = (char *)page->data;
    fwrite (buf, 1 , page->page_size , f);
    fclose (f);
}

void init_heapfile(Heapfile *heapfile, int page_size, FILE *file) {
  // Size of the each heap directory
  int  heap_size = page_size;
  // Number of slots in heap
  int numb_slots = floor((heap_size - sizeof(int)) / (2*sizeof(int)));

  // 0 indicates that there is no next heap linked to this heap
  int nextHeapID = 0;
  fwrite(&nextHeapID, sizeof(int), 1, file);
  // Move the position to after the heapID
  fseek(file, sizeof(int), SEEK_SET);

  // Preload the heap with the pageIds and free space
  for (int i = 0; i < numb_slots; i++){
      fwrite(&i, sizeof(int), 1, file);
      fwrite(&page_size, sizeof(int), 1, file);
  }

  // Reset the file position to the beginning of the file
  rewind(file);

  heapfile->page_size = page_size;
  heapfile->file_ptr = file;
}

PageID alloc_page(Heapfile *heapfile){

  rewind(heapfile->file_ptr);
  // Get header id
  int nextHeapId = 0;
  fread(&nextHeapId, sizeof(int), 1, heapfile->file_ptr);
  // Read through the header and find an empty spot
  fseek(heapfile->file_ptr, sizeof(int), SEEK_SET);

  int numb_slots = (heapfile->page_size - sizeof(int)) / (2*sizeof(int));
  // Every first slot contains the page ID, 
  // the second slot contains free space.
  PageID pageId = 0;
  int free_space  = 0;
  int curpid = 0;
  int curHeapId = 0;
  while (curpid < numb_slots*(curHeapId + 1)){
    // The position indicator of the stream is advanced by 
    // the total amount of bytes read.
    fread(&pageId, sizeof(int), 1, heapfile->file_ptr);
    fread(&free_space, sizeof(int), 1, heapfile->file_ptr);

    // Check if there is a free page in this heap directory.
    if (free_space == heapfile->page_size){
        printf("free page at : %d\n", pageId);
        rewind(heapfile->file_ptr);
        return pageId;
    }
    curpid++;
    // If free page is not found yet (end of the slots)
    if(curpid == numb_slots*(curHeapId + 1)) {
      // If there is a next heap directory linked to this heap directory
      if(nextHeapId > 0){
        // Set current HeapId to nextHeapId and continue search
        curHeapId++;
        // Advance the fileposition to the next heap directory 
        int heapOffset = (curHeapId)*(numb_slots + 1)*heapfile->page_size;
        fseek(heapfile->file_ptr, heapOffset,  SEEK_SET);

        // Get nextHeapId of current heap and store it to nextHeapId variable
        fread(&nextHeapId, sizeof(int), 1, heapfile->file_ptr);

        // Move the cursor back to the begining of the directory + one slot 
        fseek(heapfile->file_ptr, heapOffset + sizeof(int),  SEEK_SET);

        //write next heap directory
      } else {

        curHeapId++;

        // Link this  heap directory ID to previous heap directory
        int heapOffset = (curHeapId - 1)*(numb_slots + 1)*heapfile->page_size;
        fseek(heapfile->file_ptr, heapOffset , SEEK_SET);
        fwrite(&curHeapId, sizeof(int), 1, heapfile->file_ptr);

        // Initialize new Heap directory with curHeapId
        heapOffset = (curHeapId)*(numb_slots + 1)*heapfile->page_size;
        fseek(heapfile->file_ptr, heapOffset,  SEEK_SET);
        // 0 indicates that theire is no next heap linked to this heap
        nextHeapId = 0;
        fwrite(&nextHeapId, sizeof(int), 1, heapfile->file_ptr);

        // Move the position to after the heapID
        fseek(heapfile->file_ptr, heapOffset + sizeof(int),  SEEK_SET);
        // Preload the heap with the pageIds and free space
        for (int i = curpid; i < numb_slots*(curHeapId + 1); i++){
            fwrite(&i, sizeof(int), 1, heapfile->file_ptr);
            fwrite(&heapfile->page_size, sizeof(int), 1, heapfile->file_ptr);
        }
        // Move the cursor back to the begining of the directory + one slot 
        fseek(heapfile->file_ptr, heapOffset + sizeof(int),  SEEK_SET);
      }
    }
  }
  // Unexpected result
  return -1;
}

void read_page(Heapfile *heapfile, PageID pid, Page *page){
  // Number of slots in heap
  int numb_slots = (heapfile->page_size - sizeof(int)) / (2*sizeof(int));
  // Id of the heap directory in which the page with pid is located 
  int heapId = floor(pid/numb_slots);

  // Right postion of page slot with given pid and heapId.
  int pageOffset = heapfile->page_size*(heapId + 1) + heapfile->page_size * pid;
  fseek(heapfile->file_ptr, pageOffset, SEEK_SET);

  fread(page->data, sizeof(char), page->page_size/sizeof(char), heapfile->file_ptr);
  rewind(heapfile->file_ptr);
}

void write_page(Page *page, Heapfile *heapfile, PageID pid){
  // Number of slots in heap
  int numb_slots = (heapfile->page_size - sizeof(int)) / (2*sizeof(int));
  // Id of the heap directory in which the page with pid is located 
  int heapId = floor(pid/numb_slots);

  // Right position of the heap directory and page slot with given pid and heapId.
  int heapOffset = heapId*(numb_slots + 1)*heapfile->page_size;
  int pageOffset = heapfile->page_size*(heapId + 1) + heapfile->page_size * pid;

  // Set the position value to the given
  fseek(heapfile->file_ptr, pageOffset, SEEK_SET);
  char* buf = (char *)page->data;
  // Write the page
  fwrite(buf, sizeof(char), page->page_size , heapfile->file_ptr);

  // Free space slot of the page with pid in the heap directory
  int freeSlot = sizeof(int) + (pid % numb_slots) * sizeof(int) * 2 + sizeof(int);
  // Update the heap
  fseek(heapfile->file_ptr, heapOffset + freeSlot , SEEK_SET);
  int free_space = 0;
  fwrite(&free_space, sizeof(int), 1, heapfile->file_ptr);
  rewind(heapfile->file_ptr);
}
