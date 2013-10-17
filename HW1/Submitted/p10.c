#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define NUMBERS 1000
#define NUM_W 50


int read_file(char *file_r, float numbers[NUMBERS], int buffer);
int num_clear(char num[NUM_W]);

int main(int argc, char *argv[]){

	float numbers[NUMBERS];
	int i = 0;
	int j = 0;
	/* buffer is defined as the running average width minus 1*/
	int buffer = atoi(argv[2])-1;
	float sum;

	/*Could put this in a separate function but essentially
	I am adding zeroes to the front of the array so that the
	running average can begin with the specified width at
	the first element provided*/
	
	for(i=0;i<buffer;i++){
		numbers[i] = 0.0;
	}
	
	/* read_file returns the number of numbers read in*/

	for(i=buffer;i<read_file(argv[1],numbers,buffer);i++){
		sum = 0.0;
		for(j=(i-buffer);j<=i;j++){
			sum+=numbers[j];
		}
		printf("%.2f ", sum/(buffer+1));
	}
	printf("\b\n");
	return 0;
}

int read_file(char *file_r, float numbers[NUMBERS], int buffer) {

	FILE *file;
	char a[NUM_W];
	int char_n = 0;
	char c;
	int blank_flag = 1;
	int curr_float = buffer;
	
	num_clear(a);
	
	file = fopen(file_r,"r");
	
	while ((c = fgetc(file)) != EOF){
	
		if (!isspace(c) && blank_flag == 0){
			a[char_n] = c;			
			char_n++;
			blank_flag = 0;
		}
		
		else if(!isspace(c) && blank_flag == 1){
			a[char_n] = c;
			char_n++;
			blank_flag = 0;
		}
		
		else if(isspace(c) && blank_flag == 0){
			numbers[curr_float] = atof(a);
			curr_float++;
			num_clear(a);
			char_n = 0;
			blank_flag = 1;
		}
		
		else if(isspace(c) && blank_flag == 1){
			continue;
		}
	}
	
	fclose(file);
	
	return curr_float;
	
}

int num_clear(char num[NUM_W]){
	
	int i = 0;
	
	for(i=0;i<NUM_W;i++){
		num[i]='\0';
	}
	
	return 0;
}
