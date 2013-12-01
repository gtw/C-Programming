#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void zero(void *f, size_t n, size_t sz);
int main(int argc, char *argv[]){

	int n = 10;
	int i;
	int *f_i; 
	long *f_l;
	float *f_f;
	double *f_d;

	f_i = (int*)malloc(sizeof(int)*n);
	f_l = (long*)malloc(sizeof(long)*n);
	f_f = (float*)malloc(sizeof(float)*n);
	f_d = (double*)malloc(sizeof(float)*n);

	zero(f_i,n,sizeof(int));
	zero(f_l,n,sizeof(long));
	zero(f_f,n,sizeof(float));
	zero(f_d,n,sizeof(double));

	for(i=0;i<n;i++){
		printf("%d	%ld	%f	%f\n",f_i[i], f_l[i], f_f[i], f_d[i]);
	}

	return 0;
}

void zero(void *f, size_t n, size_t sz){

	memset(f,0,n*sz);

}
