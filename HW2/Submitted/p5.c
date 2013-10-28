#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void alphabetize(char *text[], int nlines);
int read_text(char ***txtptr);
int word_comp(const void *a, const void *b);
void print_text(char **txtptr, int len);

int main(int argc, char *argv[]){

	char **txtptr = (char**)malloc(sizeof(char*));
	int len;

	alphabetize(txtptr,len=read_text(&txtptr));
	print_text(txtptr,len);

	return 0;
}

/* Simple function for printing the text once read in
and sorted */

void print_text(char **txtptr, int len){

	int i;

	for(i=0;i<len;i++){

		printf("%s\n",txtptr[i]);

	}
}

/* This function dynamically allocates space for strings as they
are read in.  To begin with I pass the address of a single pointer
to a single character.  Until I reach a newline or end of file I
read into this string.  I utilize the realloc command to double
the space available for this string as necessary.  If I need to
create space for more lines of text I similarly use realloc to
double the number of pointers to lines of text I have avaialble.
The reason this function takes the address of the pointer to pointer
is that the realloc command changes the location in memory at
which an array is stored.  Changes are therefore made in **txtptr's
value throughout the read in process so by passing this &txtptr and
then dereferencing throughout the read-in I can be assured the changes
to txtptr will apply outside of the copy of it made in this function. */

int read_text(char ***txtptr){

	int line_count = 0;
	int letter_count = 0;
	int total_letters = 1;
	int total_lines = 1;
	int newl_flag = 1;
	char c;

	(*txtptr)[0] = (char*)malloc(sizeof(char));

	while((c=getchar())!=EOF){
		
		if(newl_flag == 0 && c != '\n'){
			/* Checks if we need space for more letters in this word*/			
			if(letter_count >= total_letters){
				(*txtptr)[line_count]  = (char*)realloc((*txtptr)[line_count],sizeof(char)*total_letters*2);
				total_letters = total_letters * 2;
			}
			
			(*txtptr)[line_count][letter_count] = c;
			letter_count++;	
		}

		else if(newl_flag == 0 && c == '\n'){
			
			if(letter_count >= total_letters){
				(*txtptr)[line_count] = (char*)realloc((*txtptr)[line_count],sizeof(char)*(total_letters+1));
				total_letters++;
			}
			
			(*txtptr)[line_count][letter_count] = '\0';
			letter_count = 0;
			line_count++;
			newl_flag = 1;
			/*Checks if we need space for more lines now that a '\n' has been read,
			indicating the beginning of a new word*/
			if(line_count >= total_lines){
				(*txtptr) = (char**)realloc((*txtptr),sizeof(char*)*total_lines*2);
				total_lines = total_lines*2;
			}
			/*The new line is a allocated a single character*/
			(*txtptr)[line_count] = (char*)malloc(sizeof(char));
			total_letters = 1;
		}

		else if(newl_flag == 1 && c != '\n'){
			/*The first character in a new line is set*/
			(*txtptr)[line_count][0] = c;
			letter_count++;
			newl_flag = 0;
		}

		else if(newl_flag == 1 && c == '\n'){
			/*I have decided to treat multiple new-lines as a single new-line*/
			continue;
		
		}

	}
	/*If EOF is received but there was no preceding newline I add the necessary '\0' char
	to the string, after checking that space has been allocated for it*/
	if(newl_flag == 0){
		if(letter_count >= total_letters){
			(*txtptr)[line_count] = (char*)realloc((*txtptr)[line_count],sizeof(char)*(total_letters+1));
			total_letters = total_letters+1;
		}

		(*txtptr)[line_count][letter_count] = '\0';
		line_count++;
	}
	/* I return the number of lines read*/
	return line_count;

}

void alphabetize(char *text[], int nlines){
	/*Now I just need to use qsort to sort the outer array of pointers by the
	alphabetical order of the strings they point to*/
	qsort(text,nlines,sizeof(char*),word_comp);

}

int word_comp(const void *a, const void *b){
        
        char **ai = (char**)a;
        char **bi = (char**)b;
	/* Just using strcmp as my base sorting function
	NOTE: My sort is case sensitive. */
        return strcmp(*ai,*bi);
}
