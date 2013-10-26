#include<stdio.h>
#include<stdlib.h>

double **dmatrix(size_t m, size_t n);
void print_matrix(double **f, size_t m, size_t n);
void fill_matrix(double **f, size_t m, size_t n);

int main(int arc, char * argv[]){

	int i;
	int size = atoi(argv[1]);
	double **f = dmatrix(size,size);
	
	fill_matrix(f,size,size);

	printf("Matrix with 1D indexing:\n");
		
		
		for(i=0;i<size*size;i++){
	
			printf("%.0f ",(*f)[i]);		
			if((i+1)%size == 0)
				printf("\n");
		}

	printf("Matrix with 2D indexing:\n");
	
		print_matrix(f,size,size);

	return 0;
}

double **dmatrix(size_t m, size_t n){

	int i;
	double *f_arr = (double*)malloc(sizeof(double)*m*n);
	double **f = (double**)malloc(sizeof(double*)*m);
	for(i=0;i<m;i++){
		f[i] = &f_arr[i*m];
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
