#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string.h>

int main( int argc, const char* argv[] )
{
	V name = "HELLO WORLD"; 
	V age = "1234";
	V bdate = "12/01/01"; 
 
	//Pad with empty space character
	V nameEmpty = "                                                                                           ";
	V ageEmpty = "    ";
	V bdateEmpty = "        ";
  
	Record person1;
	Record person2;
	person1.push_back(name);
	person1.push_back(age);
	person1.push_back(bdate);

	person2.push_back(nameEmpty);
	person2.push_back(ageEmpty);
	person2.push_back(bdateEmpty);


	printf("Size of the fixed serialized record person1: %d\n", fixed_len_sizeof(&person1));
	printf("Size of the fixed serialized record person2: %d\n", fixed_len_sizeof(&person2));
	
	//print out f2
	printf("\nperson2:----before read------------\n");
	for (int i = 0; i < 3; i++){
	   printf("size: %d, value: %s\n", (int)strlen(person2.at(i)), person2.at(i));
	}

	char* buffer;
	buffer = (char *)malloc(sizeof(char)*23);
	
	//write person1 to buffer   
	fixed_len_write(&person1, buffer);

	//read from buffer and store into person2
	fixed_len_read (buffer, fixed_len_sizeof(&person1), &person2); 

	//print out f2
	printf("\nperson2:----after read from buffer (buffer retrieved from person1)---------\n");
	for (int i = 0; i < 3; i++){
		printf("size: %d, value: %s\n", (int)strlen(person2.at(i)), person2.at(i));
	}

	// Prepare a fresh buffer
	char* buffer1;
	buffer1 = (char *)malloc(sizeof(char)*100);

	printf("\nBytes required for serialization of person2: %d\n", var_len_sizeof(&person2));
	var_len_write(&person2, buffer1);

	Record person3;
	V nameEmpty1 = "";
	V ageEmpty1 = "";
	V bdateEmpty1 = "";
	person3.push_back(nameEmpty1);
	person3.push_back(ageEmpty1);
	person3.push_back(bdateEmpty1);


	var_len_read(buffer1, var_len_sizeof(&person2), &person3);
	
	printf("%s\n", buffer1);
	//print out f3
	printf("person3:----after read from buffer (buffer retrieved from person2)---------\n");
	for (int i = 0; i < 3; i++){
		printf("size: %d, value: %s\n", (int)strlen(person3.at(i)), person3.at(i));
	}

	Record person4;
	V nameEmpty2 = "SasdsfasdfasdfsdfT";
	V ageEmpty2 = "ssdfdsasjkjkjkjkjksdjksjdksjdksjkdjskdjksjdksjdkjskdjskjdksjdksjkdjskdjksjdksjdkjskdjksjdksjdksjdkjskdjksjdksjdkjskdjskjdksjdksjdkjskdjskdjksjdksjdksjkdjskdjskjdksjdkjskdjskjdksjdksjdksjdksjkdjskdjskjdsjdksjdksjkdjskdjskjdksdjksjdksjdksjdkjskdjskdjksdjksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjkdjskdjskjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdksjdsdfasdfasdfafasdfasdfasdfasdfsdfasdffg";
	V bdateEmpty2 = "";
	V name2 = "SasdsfasdfasdfsdfT";
	person4.push_back(nameEmpty2);
	person4.push_back(ageEmpty2);
	person4.push_back(bdateEmpty2);
	person4.push_back(name2);

	char* buffer2;
	buffer2 = (char *)malloc(sizeof(char)*1000);
	
	printf("\nBytes required for serialization of person4: %d\n", var_len_sizeof(&person4));
	var_len_write(&person4, buffer2);

	person3.clear();
	nameEmpty1 = "";
	V name1 = "";
	ageEmpty1 = "";
	bdateEmpty1 = "";
	person3.push_back(nameEmpty1);
	person3.push_back(ageEmpty1);
	person3.push_back(bdateEmpty1);
	person3.push_back(name1);

	var_len_read(buffer2, var_len_sizeof(&person4), &person3);

	//print out f4
	printf("person3:----after read from buffer (buffer retrieved from person4)---------\n");
	int data = 0;
	int header = 0;
	for (int i = 0; i < 4; i++){
		printf("size: %d, value: %s\n", (int)strlen(person3.at(i)), person3.at(i));
		data = data + strlen(person3.at(i)); 
		header = header + sizeof(int);
	}
	printf("Total Data written: %d, Header: %d, Actual Data: %d\n", data + header, header, data);



	printf("=====================================================\n");

	Page* page = (Page *)malloc(sizeof(Page));

	init_fixed_len_page(page, 1000, 23);

	printf("Page capacity : %d =? 9\n", fixed_len_page_capacity(page));
	printf("Page freeslots : %d =? 9\n", fixed_len_page_freeslots(page));

	add_fixed_len_page(page, &person1);

	// char* _slot = (char *)page->data;
	// for (int i = 0; i < page->page_size; i ++){
	// 	printf(" %c", *_slot);
	// 	_slot++;
	// }
	// printf("\n");

	add_fixed_len_page(page, &person1);
	add_fixed_len_page(page, &person1);
	add_fixed_len_page(page, &person1);

	write_fixed_len_page(page, 5, &person2);

	printf("Page freeslots : %d =? 5\n", fixed_len_page_freeslots(page));

	Record person21;
	person21.push_back(nameEmpty);
	person21.push_back(ageEmpty);
	person21.push_back(bdateEmpty);

	printf("Size of the fixed serialized record person21: %d\n", fixed_len_sizeof(&person21));
	read_fixed_len_page(page, 0, &person21);

	char* fname = "test";
	write_page_to_file(fname, page);

}