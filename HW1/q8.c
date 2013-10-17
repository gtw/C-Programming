#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]){

	float 	num_f 	= atof(argv[1]);
	/* this is the crucial step which allows me to perform
	bitwise operations on a number originally stored as a float */
	unsigned long 	num_i 	= *(unsigned long*)&num_f;
	unsigned long 	a 	= 1;
	unsigned long	b;
	int 	c;
	
	/*I use the bitwise & operation on one bit at a time and then
	move the result down to the first bit of the number, resulting in
	either a 0 or 1.  This is just printed as a long*/

	b = a<<31;
	
	/*prints sign*/
	printf("%ld ",((b&num_i)>>31));
	
	/*prints exponent*/
	for(c=0;c<8;c++){
		b=(a<<(30-c));
		printf("%ld",((b&num_i)>>(30-c)));
	}
	printf(" ");
	
	/*prints mantissa*/
	for(c=0;c<23;c++){
		b=(a<<(22-c)) ;
		printf("%ld",((b&num_i)>>(22-c)));
	}

	printf("\n");
	return 0;
}

