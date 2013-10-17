#include <stdio.h>

int main(int agrc, char **argv)
{

	FILE *file;
	int c;
	char *filename = argv[1];

	file = fopen(filename, "r");

	/* below loop just reads every characeter
	and if it is a tab prints two spaces rather
	than the character*/
	
	while ((c = fgetc(file)) != EOF){

		if (c == '\t')
			printf("  ");
		else putchar(c);
	
	}
	
	return 0;

}	
