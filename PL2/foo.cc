#include <stdio.h>
#include <stdlib.h>
#include "library.h"
int main( int argc, const char* argv[] )
{
	Record fuckers;
	for (int i = 0; i < 11; i++){
		V test = "aa";
		fuckers.push_back(test);
	}

	printf("%d\n", fixed_len_sizeof(&fuckers));

	char* buffer;
 	fixed_len_write(&fuckers, buffer);
        printf("%c\n", buffer[0]);
// // 
	// for (int i = 0; i < 10; i++){
	// 	printf("%c\n", buffer[i]);
	// 	printf("\n");
	// }
}
