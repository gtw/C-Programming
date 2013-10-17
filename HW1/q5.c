#include <stdio.h>
#include <stdlib.h>
#define WORDS 1000

int main(int argc, char * argv[]){
	
	int 	num = atoi(argv[1]);
	int 	num_copy = 0;
	int 	*np = &num;
	char 	*ncp = &(*np);
	int 	*copypn = &num_copy;
	char 	*copypc = &(*copypn);

	*copypc = *(ncp+3);
	copypc++;
	*copypc = *(ncp+2);
	copypc++;
	*copypc = *(ncp+1);
	copypc++;
	*copypc = *ncp;
	printf("%d",*copypn);

		




	return 0;
}
