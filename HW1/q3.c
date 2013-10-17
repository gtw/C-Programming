#include <stdio.h>
#define MAX_LINES 1000
#define MAX_CHAR_PER_LINE 1000

int read_file(char *,int text[MAX_LINES][MAX_CHAR_PER_LINE]);
int print_file(int text[MAX_LINES][MAX_CHAR_PER_LINE]);

int main(int argc, char **argv)
{

	int text[MAX_LINES][MAX_CHAR_PER_LINE];
	char *file_r = argv[1];
	int i, j;
	for(i=0;i<MAX_LINES;i++){
		for(j=0;j<MAX_CHAR_PER_LINE;j++){
			text[i][j]=0;
		}
	}
	
	read_file(file_r,text);
	print_file(text);

	return 0;	

}

int read_file(char *file_r, int text[MAX_LINES][MAX_CHAR_PER_LINE]) {

	FILE *file;
	int line_n = 0;
	int char_n = 0;
	int c = 0;

	file = fopen(file_r,"r");
	
	while ((c = fgetc(file)) != EOF){
		if (c == '\n'){
			text[line_n][char_n] = c;			
			line_n++;
			char_n = 0;
		}
		else {
			text[line_n][char_n] = c;
			char_n++;
		}
	
	}

	return 0;
}

int print_file(int text[MAX_LINES][MAX_CHAR_PER_LINE]) {

	int 	line_n;
	int 	char_n;

	for(line_n = 0; line_n < MAX_LINES; line_n++) {
		for(char_n = 0; char_n < MAX_CHAR_PER_LINE; char_n++){
			if (text[line_n][char_n]=='o'){
				printf("Carlos");
			}
			else {
				printf("%c", text[line_n][char_n]);
			}	
		}
	}
	return 0;
}
