#include <stdlib.h>
#include <stdio.h>

int main(int argc, char * argv[]){

	srand(42);
	printf("%f\n",( ((double) rand() - (RAND_MAX/2.0)) / ((RAND_MAX+1.0)/2.0)));
	
	return 0;
}
