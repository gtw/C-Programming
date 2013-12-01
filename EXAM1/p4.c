#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TOKEN_LEN 50
#define MAX_TOKENS 100

int tokenize(char tokens[][MAX_TOKEN_LEN], char *str, char c);

int main(int argc, char *argv[]){

	int i,j;
	char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
	int n;
	
	char * words = "Hello;my;name;is;Andrew";

	for(i=0;i<MAX_TOKENS;i++){
		for(j=0;j<MAX_TOKEN_LEN;j++){
			tokens[i][j] = '\0';
		}
	}

	n =  tokenize(tokens, words, ';');

	for(i=0;i<n;i++){
		printf("tokens[%d]:%s\n",i,tokens[i]);
	}

	return 0;

}

int tokenize(char tokens[][MAX_TOKEN_LEN], char *str, char c){

	int n = 0;
	int char_n = 0;
	int line_n = 0;
	int delim_flag = 1;
	while(*str!='\0'){
		if(*str!=c && delim_flag == 1){
			tokens[line_n][char_n] = *str;
			delim_flag = 0;
			char_n++;
		}
		else if(*str!=c && delim_flag == 0){
			tokens[line_n][char_n] = *str;
			char_n++;
		}
		else if(*str==c){
			line_n++;
			char_n = 0;	
			n++;
			delim_flag = 1;
		}
		str++;
	}
	tokens[line_n][char_n] = '\0';

	return n+1;
}
