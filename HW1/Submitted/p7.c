#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int input = atoi(argv[1]);

	/* 255 is binary 11111111 (8 1's) so I just use the bitwise & to pull
	each byte of the integer and then the bitwise or to rearrange them*/

	int a = 255;
	int b = a<<8;
	int c = a<<16;
	int d = a<<24;
	int final = ((input&a)<<24)|((input&b)<<8)|((input&c)>>8)|((input&d)>>24);

	/*Printing the rearranged bit pattern as an integer*/

	printf("%d\n",final);

	return 0;
}
