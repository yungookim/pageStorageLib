#include <stdio.h>
#include <stdlib.h>
#include "library.h"
int main( int argc, const char* argv[] )
{
    V name = "HELLO WORLD"; 
    V age = "1234";
    V bdate = "12/01/01"; 
 
    //Pad with empty space character
    V nameEmpty = "           ";
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


    printf("Size of the serialized record person1: %d\n", fixed_len_sizeof(&person1));
    printf("Size of the serialized record person2: %d\n", fixed_len_sizeof(&person2));
    
    //print out f2
    printf("\nperson2:----before read------------\n");
    for (int i = 0; i < 3; i++){
	printf("size: %d, value: %s\n", (int)strlen(person2.at(i)), person2.at(i));
    }

    char* buffer;
    buffer = (char *)malloc(sizeof(char *));
    
    //write person1 to buffer   
    fixed_len_write(&person1, buffer);

    //read from buffer and store into person2
    fixed_len_read (buffer, 23, &person2); 

    //print out f2
    printf("\nperson2:----after read from buffer (buffer retrieved from person1)---------\n");
    for (int i = 0; i < 3; i++){
        printf("size: %d, value: %s\n", (int)strlen(person2.at(i)), person2.at(i));
    }
}
