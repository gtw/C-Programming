#include <stdio.h>

int main(int agrc, char **argv)
{

	FILE *file;
	int c;
	char *filename = argv[1];

	file = fopen(filename, "r");
	
	while ((c = fgetc(file)) != EOF){

		if (c == '\t')
			printf("  ");
		else putchar(c);
	
	}
	
	return 0;

}	
