#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

int j;

void catch_function(int signal){

	printf("segmentation fault at loop index: %d\n",j);
	exit(1);

}
	
int main(int arc, char *argv[]){

	int *data = (int*)malloc(sizeof(int)*10);

	signal(SIGSEGV,catch_function);

	for(j=0;1;j++){
		data[j]=0;
	}

	return 0;
}
