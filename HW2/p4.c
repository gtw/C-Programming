#include<stdio.h>
#include<stdlib.h>

void heapify(int *f, int n);
int * allocate_array( int arc, char *argv[]);
int left(int i , int n);
int right(int i , int n);
void pushdown(int *f, int i, int n);
void swap(int *f, int j, int k);
void print_array(int *f, int n);
	
int main(int argc, char *argv[]){

	int * arr = allocate_array(argc, argv);

	print_array(arr,argc-1);
	heapify(arr,argc-1);
	
	return 0;
}


int * allocate_array( int argc, char *argv[]){

	int i;
	int * arr = (int*)malloc((argc-1)*sizeof(int));

	for(i=0;i<argc-1;i++){
		arr[i] = atoi(argv[i+1]);	
	}

	return arr;
}

void print_array(int *f, int n){

	int i;
	
	for(i=0;i<n;i++)
		printf("%-6d ",f[i]);

	printf("\n");
}

void heapify(int *f, int n){

	int i;

	for(i=(n-2)/2;i>=0;i--){
	
		printf("Pushing Down at Address %d of %d\n", i+1, n);
		pushdown(f,i,n);
		print_array(f,n);
	
	}
}

void pushdown(int *f, int i, int n){

	int largest;
	int l = left(i,n);
	int r = right(i,n);
	
	if(l != -1  && f[l] > f[i])
		largest = l;
	else
		largest = i;

	if(r != -1 && f[r] > f[largest])
		largest = r;
	
	if(largest != i){
		swap(f,i,largest);
		pushdown(f,largest,n);
	}
}

void swap(int *f, int j, int k){

	int temp = f[j];
	f[j] = f[k];
	f[k] = temp;

}

int left(int i, int n){

	if(2*i + 1 < n)
		return 2*i + 1;
	else
		return -1;
}
		
int right(int i, int n){

	if(2*i + 2 < n)
		return 2*i + 2;
	else
		return -1;
}
