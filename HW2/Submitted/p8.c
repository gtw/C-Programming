#include<stdio.h>
#include<stdlib.h>

double ***dmatrix(size_t l, size_t m, size_t n);
void print_matrix(double ***f, size_t l, size_t m, size_t n);
void fill_matrix(double ***f, size_t l, size_t m, size_t n);

int main(int arc, char * argv[]){

	int i;
	int size = atoi(argv[1]);
	double ***f = dmatrix(size,size,size);
	
	fill_matrix(f,size,size,size);

	printf("Matrix with 1D indexing:\n");
		
		
		for(i=0;i<size*size*size;i++){
	
			printf("%.0f ",(**f)[i]);		
			if((i+1)%size == 0)
				printf("\n");
			if((i+1)%(size*size) == 0)
				printf("\n");
		}

	printf("Matrix with 3D indexing:\n");
	
		print_matrix(f,size,size,size);

	return 0;
}

double ***dmatrix(size_t l, size_t m, size_t n){

	int i, j;
	double *f_doubles 	= (double*)malloc(sizeof(double)*l*m*n);
	double **f_double_ptrs 	= (double**)malloc(sizeof(double*)*l*m);
	double ***f 		= (double***)malloc(sizeof(double**)*l);

	for(i=0;i<l;i++){
		f[i] = &f_double_ptrs[i*m];
		for(j=0;j<m;j++){
			f[i][j] = &f_doubles[i*(m*n)+j*n];
		}
	}

	return f;
}

void fill_matrix(double ***f, size_t l, size_t m, size_t n){

	int i, j, k;
	for(i=0;i<l;i++){
		for(j=0;j<m;j++){
			for(k=0;k<n;k++){
				f[i][j][k] = i*(m*n)+j*n+k;
			}
		}
	}
}

void print_matrix(double ***f, size_t l, size_t m, size_t n){

	int i, j, k;
	for(i=0;i<l;i++){
		for(j=0;j<m;j++){
			for(k=0;k<n;k++){
				printf("%.0f ",f[i][j][k]);
			}
			printf("\n");
		}
		if(i!=(l-1)){
			printf("\n");
		}
	}
}
