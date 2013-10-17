#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int	i;
	int 	curr_y;
	

	for ( i = 1; i < argc; i++ ) {
	
		curr_y = atoi(argv[i]);

		if (curr_y%400 == 0 || (curr_y%100 != 0 && curr_y%4 == 0)) {
			printf("%d\n",curr_y);
		}
	}

	return 0;

}
