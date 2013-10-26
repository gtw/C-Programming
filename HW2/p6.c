#include<stdio.h>
#include<stdlib.h>

double **dmatrix(size_t m, size_t n);
void print_matrix(double **f, size_t m, size_t n);
void fill_matrix(double **f, size_t m, size_t n);

int main(int arc, char * argv[]){

	int size = atoi(argv[1]);
	double **f = dmatrix(size,size);
	
	fill_matrix(f,size,size);
	print_matrix(f,size,size);

	return 0;
}

double **dmatrix(size_t m, size_t n){

	int i;
	double **f = (double**)malloc(sizeof(double*)*m);
	for(i=0;i<m;i++){
		f[i] = (double*)malloc(sizeof(double)*n);
	}
	return f;
}

void fill_matrix(double **f, size_t m, size_t n){

	int i, j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			f[i][j] = (i*n)+j;
		}
	}
}

void print_matrix(double **f, size_t m, size_t n){

	int i, j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("%.0f ",f[i][j]);
		}
		printf("\n");
	}
}
