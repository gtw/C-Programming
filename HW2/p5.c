#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void alphabetize(char *text[], int nlines);
int read_text(char **txtptr);
int word_comp(const void *a, const void *b);

int main(int argc, char *argv[]){

	char **txtptr = (char**)malloc(sizeof(char*));
	int len, i;

	len = read_text(txtptr);
		
	alphabetize(txtptr,len);
	
	for(i=0;i<len;i++){
		printf("%s\n",txtptr[i]);
	}
	return 0;
}

int read_text(char **txtptr){

	int line_count = 0;
	int letter_count = 0;
	int total_letters = 1;
	int total_lines = 1;
	
	char c = getchar();

	while(c!=EOF){
		
		if(line_count >= total_lines){
			txtptr = (char**)realloc(txtptr,sizeof(char*)*total_lines*2);
			total_lines = total_lines * 2;
		}
		
		txtptr[line_count] = (char*)malloc(sizeof(char));
		total_letters = 1;

		while(c!='\n' && c != EOF){
			printf("%c",c);
			if(letter_count >= total_letters){
				txtptr[line_count] = (char*)realloc(txtptr[line_count],sizeof(char)*total_letters*2);
				total_letters = total_letters * 2;
			}
			txtptr[line_count][letter_count] = c;
			letter_count++;
			c = getchar();
		}
		
				
		if(letter_count >= total_letters){
			txtptr[line_count] = (char*)realloc(txtptr[line_count],sizeof(char)*total_letters*2);
			total_letters = total_letters * 2;
		}
		txtptr[line_count][letter_count] = '\0';
		letter_count = 0;
		line_count++;
		if(c!=EOF){
			getchar();
		}
	}

	return line_count;
}

void alphabetize(char *text[], int nlines){

	qsort(text,nlines,sizeof(char*),word_comp);

}

int word_comp(const void *a, const void *b){
        
        char *ai = (char*)a;
        char *bi = (char*)b;

        return strcmp(ai,bi);
}
