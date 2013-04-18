#Page based persistance storage library.#
  
Code is based on the submitted assignments from Database System Technology CSC443, Winter 2013, at University of Toronto.

##Specification are as follows##
  
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


##Graphs##

####Querying performances versus SQLite

<img src="https://dl.dropboxusercontent.com/u/36220055/1.png"></img>

<img src="https://dl.dropboxusercontent.com/u/36220055/2.png"></img>

<img src="https://dl.dropboxusercontent.com/u/36220055/3.png"></img>
