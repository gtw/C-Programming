#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_CHAR_PER_LINE 50
/* I assume no more than 1000 words of 50 characters max*/

int read_file(char *file_r, char words[MAX_LINES][MAX_CHAR_PER_LINE]);
int word_clear(char words[MAX_LINES][MAX_CHAR_PER_LINE]);
int num_clear(int nums[MAX_LINES]);
int uniq_word_count(char words[MAX_LINES][MAX_CHAR_PER_LINE], 
		char uniq_words[MAX_LINES][MAX_CHAR_PER_LINE],
		int uniq_count[MAX_LINES]);
int remove_non_dups(char words[MAX_LINES][MAX_CHAR_PER_LINE]);
int line_clear(char word[MAX_CHAR_PER_LINE]);

int main(int argc, char *argv[]){

	char words[MAX_LINES][MAX_CHAR_PER_LINE];
	char uniq_words[MAX_LINES][MAX_CHAR_PER_LINE];
	int uniq_count[MAX_LINES];
	int i;

	/* I clear out "words" which will hold all words read in,
	"uniq_words" which will be used to build a list of unique words
	and "uniq_count", which hold the count of unique words*/
	
	word_clear(words);
	word_clear(uniq_words);
	num_clear(uniq_count);
	
	/* I read in the specified text file */
		
	read_file(argv[1], words);

	/* I remove words that do not have duplicate letters from the
	file by setting them to null*/

	remove_non_dups(words);

	/* uniq_word_count moves the values from words to uniq_words
	while simultaneously counting their instances.  Since "uniq_word_count"
	returns the number of uniq words in the file, I can then iterate over
	those obs to print them and the number of instances that occur */

	for(i=0;i<uniq_word_count(words,uniq_words,uniq_count);i++){
		printf("%s: %d\n",uniq_words[i],uniq_count[i]);
	}
	
	return 0;	

}

int remove_non_dups(char words[MAX_LINES][MAX_CHAR_PER_LINE]){

	int i,j,dup_flag;

	for(i=0;i<MAX_LINES;i++){

		j=1;
		dup_flag = 0;
		/*I assume a word has no duplicates and then
		begin searching for duplicate letters in contiguous words.
		Note that j begins at 1 not zero since I look one observation
		back (i.e. from a[1] to a[0]).  If there are no dups the word
		is set to all NULL by "line_clear" and so it will be ignored
		by the "uniq_words_count" function.*/

		while(words[i][j]!='\0'){
			if(words[i][j] == words[i][j-1]){
				dup_flag = 1;
				break;
			}
			j++;
		}
		
		if(dup_flag==0){
			line_clear(words[i]);
		}
	}

	return 0;
}

int line_clear(char word[MAX_CHAR_PER_LINE]){
	
	int i;
	for(i=0;i<MAX_CHAR_PER_LINE;i++){
		word[i]='\0';
	}
	return 0;
}
		
int uniq_word_count(char words[MAX_LINES][MAX_CHAR_PER_LINE], 
		char uniq_words[MAX_LINES][MAX_CHAR_PER_LINE],
		int uniq_count[MAX_LINES]){

	int word_count = 0;
	int i, j, uniq_flag;

	/* For each word I begin by assuming it is unique and then
	comparting it to the list of words previously identified as
	unique.  If it is idnetical to a word in "uniq_words" I increment
	the associated value in uniq_count and move on to the next word.
	If it is indeed unique and not the null string then I add it to
	the end of uniq_words and set the uniq_count counter at that instance
	to 1.  Finally I return the number of unique words added*/

	for(i=0;i<MAX_LINES;i++){
		uniq_flag = 1;
		for(j=0;j<word_count;j++){
			if(strcmp(words[i],uniq_words[j])==0){
				uniq_count[j]++;
				uniq_flag = 0;
				break;
			}			
		}
		if(uniq_flag == 1 && words[i][0]!='\0'){
			strcpy(uniq_words[word_count],words[i]);
			uniq_count[word_count] = 1;
			word_count++;	
		}
	}

	return word_count;
}

int read_file(char *file_r, char words[MAX_LINES][MAX_CHAR_PER_LINE]){

	FILE *file;
	int line_n = 0;
	int char_n = 0;
	char c;
	int blank_flag = 1;
	
	/*Re-clear the "words" array, in case read_file later is used to
		read into a populated array*/
		
	word_clear(words);
	file = fopen(file_r,"r");
	
	while ((c = fgetc(file)) != EOF){
	
		if (!isspace(c)){
			words[line_n][char_n] = c;
			char_n++;
			blank_flag = 0;
		}
		
		else if(isspace(c) && blank_flag == 0){
			line_n++;
			char_n = 0;
			blank_flag = 1;
		}
		
		else if(isspace(c) && blank_flag == 1){
			continue;
		}
	}
	
	fclose(file);
	
	return line_n;
	
}

int word_clear(char words[MAX_LINES][MAX_CHAR_PER_LINE]){
	
	int i, j;
	
	for(i=0;i<MAX_LINES;i++){
		for(j=0;j<MAX_CHAR_PER_LINE;j++){
			words[i][j]='\0';
		}
	}
	return 0;
}

int num_clear(int nums[MAX_LINES]){
	
	int i;
	
	for(i=0;i<MAX_LINES;i++){
		nums[i]=0;
	}
	
	return 0;
}
