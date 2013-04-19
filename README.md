#Page based persistance storage library.#
  
Code is based on the submitted assignments from Database System Technology CSC443, Winter 2013, at University of Toronto.

##Specifications are as follows##
  
###Directory based heap file###
Images taken from http://dblab.cs.toronto.edu/courses/443/2013/03.data-layout.html

<img src="https://dl.dropboxusercontent.com/u/36220055/directory-heapfile2.png"></img>
  
###Page format for fixed length records

<img src="https://dl.dropboxusercontent.com/u/36220055/fixed-page.png"></img>
  
###Requirements  
  * offers efficient append of new data,
  * supports sequential scanning,
  * does not offer random access.
  * Data exists on secondary storage: it's designed to efficient for large data volume, with capacity only limited by the available secondary storage.
  * A heap file can span over multiple disks or machines: heap file can use large addressing schemes to span across multiple disks or ever networks.
  * Data is organized into pages.
  * Pages can be partially empty.
  * Pages may be segmented over different physical regions of a hard drive, or may be scattered over different drives, or even across different networks. We simply assume that each page is a unique page ID of the type PageAddress, and the operating system can locate the page for us.

Every page p as an entry in the heap directory of (page_offset, freespace). The page ID of p can be the 
index of its entry in the directory. We call this: ID(p).  
  
Every record r is stored at some slot in some page p. The record ID, ID(r) is the contenation of ID(p) 
and the slot index in p.  

Suppose we have the following parameters:

```
Page size         : 16 KB	 
Page address size	: 32 bits  
Each entry in the directory would be:  
  Bits for free space+Bits for page address  
  = log2(16 KB)+32=17+32 bits = 49 bits  
  
Thus, each directory page can index up to: 16 KB49 bits=2674 pages=42 MB
```

###API###

```C
/**
 * Compute the number of bytes required to serialize record
 */
int fixed_len_sizeof(Record *record);

/**
 * Serialize the record to a byte array to be stored in buf.
 */
void fixed_len_write(Record *record, void *buf);

/**
* Deserializes from `size` bytes from the buffer, `buf`, and
* stores the record in `record`.
*/
void fixed_len_read(void *buf, int size, Record *record);

/**
 * Compute the number of bytes required to serialize record
 */
int var_len_sizeof(Record *record);

/**
 * Serialize the record using variable record encoding
 */
void var_len_write(Record *record, void *buf);

/**
 * Deserialize the `buf` which contains the variable record encoding.
 */
void var_len_read(void *buf, int size, Record *record);

/**
 * Initializes a page using the given slot size
 */
void init_fixed_len_page(Page *page, int page_size, int slot_size);
 
/**
 * Calculates the maximal number of records that fit in a page
 */
int fixed_len_page_capacity(Page *page);
 
/**
 * Calculate the free space (number of free slots) in the page
 */
int fixed_len_page_freeslots(Page *page);

/**
 * Add a record to the page
 * Returns:
 *   record slot offset if successful,
 *   -1 if unsuccessful (page full)
 */
int add_fixed_len_page(Page *page, Record *r);
 
/**
 * Write a record into a given slot.
 */
void write_fixed_len_page(Page *page, int slot, Record *r);
 
/**
 * Read a record from the page from a given slot.
 */
void read_fixed_len_page(Page *page, int slot, Record *r);

void write_page_to_file(char* fname, Page* page);

/**
 * Initalize a heapfile to use the file and page size given.
 */
void init_heapfile(Heapfile *heapfile, int page_size, FILE *file);

/**
 * Allocate another page in the heapfile.  This grows the file by a page.
 */
PageID alloc_page(Heapfile *heapfile);

/**
 * Read a page into memory
 */
void read_page(Heapfile *heapfile, PageID pid, Page *page);

/**
 * Write a page from memory to disk
 */
void write_page(Page *page, Heapfile *heapfile, PageID pid);

/**
 *  Initialize record iterator
 */
void init_record_iterator(RecordIterator *iterator, Heapfile *heapfile, 
	int slot_size, int page_size);

/**
 *  Move the iterator to the next record
 */
void iterate_record(RecordIterator *iterator);

/**
 *  Read the current record
 */
void read_current_record(RecordIterator *iterator, Record *record);
```



##Graphs##

###Querying performances versus SQLite

Parametrized SQL query
```sql
SELECT SUBSTRING(A2, 1, 5), COUNT(*) FROM T
        WHERE A1 >= start AND A1 <= end
        GROUP BY SUBSTRING(A2, 1, 5) 
```


<img src="https://dl.dropboxusercontent.com/u/36220055/1.png"></img>

<img src="https://dl.dropboxusercontent.com/u/36220055/2.png"></img>

<img src="https://dl.dropboxusercontent.com/u/36220055/3.png"></img>
