#include<stdio.h>
#include<stdlib.h>

void heapify(int *f, int n);
int * allocate_array( int arc, char *argv[]);
int left(int i , int n);
int right(int i , int n);
void pushdown(int *f, int i, int n);
void swap(int *f, int j, int k);
int test_heap( int * f, int n);
	
int main(int argc, char * argv[])
{
	int result;
	int i;
	int n = argc - 1;
	int * arr = allocate_array( argc, argv );

	heapify( arr, n );
	result = test_heap( arr, n );

	for( i = 0; i < n; i++ )
		printf("%d ", arr[i]);
	printf("\n");

	if( result == 1 )
		printf("Heap test success!\n");
	else
		printf("Heap test failed.\n");

	free(arr);

	return 0;
}

int test_heap( int * f, int n)
{
	int i;
	int child_A, child_B;

	for( i = 0; i < n; i++ )
	{
		child_A = ( 2 * i ) + 1;
		child_B = ( 2 * i ) + 2;

		if( child_A < n )
			if( f[i] < f[child_A] )
				return -1;
		
		if( child_B < n )
			if( f[i] < f[child_B] )
				return -1;
	}

	return 1;
}

int * allocate_array( int argc, char *argv[]){

	int i;
	int * arr = (int*)malloc((argc-1)*sizeof(int));

	for(i=0;i<argc-1;i++){
		arr[i] = atoi(argv[i+1]);	
	}

	return arr;
}

void heapify(int *f, int n){

	int i;

	for(i=(n-2)/2;i>=0;i--){
	
		pushdown(f,i,n);
	
	}
}

/* Pushdown and in fact this entire algorithm operates
by assuming all elements in an array to the right of the given
element are a stack, with the possible exception of that element's
children.  It then pushes down that element should it be smaller
than one of its children, swapping it for the larger of the two.
This process continues until the element has no children or is larger
than its child elements.  As mentioned in my README I am implementing
an algorithm I found online. */

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

/*Left and Right determine the index of the left and right
child elements of element i in a help of n elements */

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
