#include <stdio.h>
#include <stdlib.h>
#define DICT_L 4994
#define WORD_L 4 

int read_file(char *,int text[DICT_L][WORD_L]);
int print_file(int text[DICT_L][WORD_L]);
int equal_word(int a[], int b[]);
int compare(const void *a, const void *b);

int main(int argc, char **argv)
{

	int text[DICT_L][WORD_L];
	int i, j, k, l;
	int lib[DICT_L][WORD_L];
	int word[WORD_L];
	
	read_file("dictionary.txt", text);
	read_file("dictionary.txt", lib);
	
	for(i=0;i<DICT_L;i++){
		qsort(lib[i],WORD_L,sizeof(int),compare);
	}

	for(i=1;i<argc;i++){
		for(j=0;j<WORD_L;j++){
			word[j] = (int)argv[i][j];
		}
		qsort(word,WORD_L,sizeof(int),compare);
		printf("%s: ",argv[i]);
		for(k=0;k<DICT_L;k++){
			if(equal_word(word,lib[k])==1){
				for(l=0;l<WORD_L;l++){
					printf("%c",text[k][l]);
				}
			printf(" ");
			}
		}

		printf("\n");
			
	}
	
	return 0;	
	
}

int equal_word(int a[4], int b[4]){

	int i;
	for(i=0;i<4;i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	return 1;
}

int compare(const void *a, const void *b){
	
	int *ai = (int*)a;
	int *bi = (int*)b;

	return ((*ai>*bi) - (*ai<*bi));
}	

int read_file(char *file_r, int text[DICT_L][WORD_L]) {

	FILE *file;
	int line_n = 0;
	int char_n = 0;
	int c = 0;

	file = fopen(file_r,"r");
	
	while ((c = fgetc(file)) != EOF){
		if (c == '\n'){
			/*no longer keep newlines*/	
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

int print_file(int text[DICT_L][WORD_L]) {

	int 	line_n;
	int 	char_n;

	for(line_n = 0; line_n < DICT_L; line_n++) {
		for(char_n = 0; char_n < WORD_L; char_n++){
			printf("%c", text[line_n][char_n]);
		}
		printf("\n");
	}
	return 0;
}
