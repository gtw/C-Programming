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

	/* I read in two copies of the library.  The first "text"
	will remain unchanged for printing original values. "lib"
	will be sorted and then compared to sorted versions of
	the words read in from argv*/
	
	read_file("dictionary.txt", text);
	read_file("dictionary.txt", lib);
	
	for(i=0;i<DICT_L;i++){
		qsort(lib[i],WORD_L,sizeof(int),compare);
	}

	for(i=1;i<argc;i++){
		for(j=0;j<WORD_L;j++){
			word[j] = (int)argv[i][j];
		}
		/*word is sorted below to compare to the values
		in the "lib" version of the dictionary*/
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

/* Probably could've done something with strcmp here*/

int equal_word(int a[WORD_L], int b[WORD_L]){

	int i;
	for(i=0;i<WORD_L;i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	return 1;
}

/* Used by qsort. */

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

