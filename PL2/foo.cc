#include <stdio.h>
#include "library.h"
int main( int argc, const char* argv[] )
{
	Record fuckers;
	for (int i = 0; i < 11; i++){
		V test = "aa";
		fuckers.push_back(test);
	}

	printf("%d\n", fixed_len_sizeof(&fuckers));

	unsigned char* buffer;
	fixed_len_write(&fuckers, buffer);
	/*
	for (int i = 0; i < 10; i++){
		printf(fuck[i]);
		printf("\n");
	}
	*/
}
