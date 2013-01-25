#include <stdio.h>
#include "library.h"
int main( int argc, const char* argv[] )
{
	Record fuck;
	for (int i = 0; i < 11; i++){
		V test = "aaa";
		fuck.push_back(test);
	}
	printf( "\nHello World\n\n" );
	printf("%d\n", fixed_len_sizeof(&fuck));

	int buffer[33];
	fixed_len_write(&fuck, buffer);
	/*
	for (int i = 0; i < 10; i++){
		printf(fuck[i]);
		printf("\n");
	}
	*/
}
