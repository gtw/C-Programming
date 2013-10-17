#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int permute(char word[], int start, int end);
int compare_char(const void *a, const void *b);
void swap (char *a, char *b);
void gen_perms(char *word, int start, int end);

int main(int argc, char *argv[]){

	int i = 1;
	while(i<argc){
		printf("permutations of : %s\n",argv[i]);
		permute(argv[i],0,strlen(argv[i]));	
		i++;
	}

	
	return 0;
}

/* I sort the array first so that at least for smaller words
I will have my results in alpha. order.  I would need to
write another sorting function to have this work for longer
words.  Subsequently, however, everything is sent to gen_perms
which handles the in place permutation process.  As noted in
my READ-ME, while I understand this code well, it was influenced
in large part by resources I found online.  I AM NOT PRESENTING
THIS WORK AS MY OWN, I JUST WANTED TO KNOW HOW THIS WOULD BE
IMPLEMENTED*/

int permute(char word[], int start, int end){

	qsort(word,end,sizeof(char),compare_char);
	gen_perms(word,0,end-1);
	return 0;
}

/* I received some help writing the compare functions for my
qsort calls online.  In particular the "const void" declaration
and the use of inequalities rather than subtraction was clever
so I wanted to use it*/

int compare_char(const void *a, const void *b){
	
	char *ai = (char*)a;
	char *bi = (char*)b;

	return ((*ai>*bi) - (*ai<*bi));
}

/* See note above regarding source */

void swap (char *x, char *y){

	char z;
	z = *x;
	*x = *y;
	*y = z;

}

void gen_perms(char *a, int start, int end){

	int j;
	if(start == end){
		printf("%s\n",a);
	}
	else{
		for(j = start; j <= end; j++){
			swap((a+start),(a+j));
			gen_perms(a, start+1, end);
			swap((a+start),(a+j));
		}
	}
}


