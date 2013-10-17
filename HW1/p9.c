#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

int atoi2(char *num);

int main(int argc, char *argv[]){
	
	if(atoi2(argv[1])==-1){
		fprintf(stderr,"ERROR: -1\n");
	}
	else if(atoi2(argv[1])==-2){
		fprintf(stderr,"ERROR: -2\n");
	}
	else if (atoi2(argv[2])==-1){
		fprintf(stderr,"ERROR: -1\n");
	}
	else if(atoi2(argv[2])==-2){
		fprintf(stderr,"ERROR: -2\n");
	}
	else{
		printf("%d\n", atoi2(argv[1])+atoi2(argv[2]) );
	}
	
	return 0;
}


/* the cytpe header makes it easy to check if non-digits are entered.
Then I simply check in those instances whether the character is a decimal
point and write the appropriate error to stderr.  Information on stderr
was taken from C Programming Vol 2*/

int atoi2(char *num){
	
	char *num2 = num;
	
	while(*num2!='\0'){
		if(!isdigit(*num2)){
			if(*num2=='.'){
				return -2;
			}
			else{
				return -1;
			}
		}
		num2++;
	}
	
	return atoi(num);
}
