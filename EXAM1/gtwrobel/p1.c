#include<stdio.h>
#include<stdlib.h>

void setvals(int *f, int n, int m);
int main(int argc, char *argv[]){

	int n = 10, m = 51;
	int i;
	int *f; f = (int*)malloc(sizeof(int)*n);
	setvals(f,n,m);
	
	for(i=0;i<n;i++){
		printf("%d\n",f[i]);
	}

	return 0;
}

void setvals(int *f, int n, int m){

	int i;

	for(i=0;i<n;i++){
		f[i]=m;
	}
}
