#include<stdio.h>
#include<stdlib.h>

void abs_sort(int *f, int n);
int abs_comp(const void *a, const void *b);

int main(int argc, char *argv[]){

	int i;
	int *f = (int*)malloc(sizeof(int)*(argc-1));

	for(i=0;i<argc-1;i++){
		f[i] = atoi(argv[i+1]);
	}

	abs_sort(f,argc-1);

	for(i=0;i<argc-1;i++){
		printf("%d ",f[i]);
	}

	printf("\n");

	return 0;
}

void abs_sort(int *f, int n){

	qsort(f,n,sizeof(int),abs_comp);

}

int abs_comp(const void *a, const void *b){

	int *ai = (int*)a;
	int *bi = (int*)b;
	/* I make use of the abs function from stdlib */
	return (abs(*ai) < abs(*bi)) - (abs(*ai) > abs(*bi));
} 
