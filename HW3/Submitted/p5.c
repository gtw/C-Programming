#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct arraylist{

	int sz;
	int cap;
	int *data;
	
	int (*append)(struct arraylist * list, int val);
	int (*print)(struct arraylist * list);
	int (*set)(struct arraylist * list, int val, int index);
	int (*insert)(struct arraylist * list, int val, int index);
	int (*destroy)(struct arraylist * list);
	int (*valueOf)(struct arraylist * list, int element);
	int (*size)(struct arraylist * list);
	int (*capacity)(struct arraylist * list);

} ArrayList;

int append(ArrayList * list, int val);
int print( ArrayList * list );
int set( ArrayList * list, int val, int index );
int insert(ArrayList * list, int val, int index);
int destroy( ArrayList * list );
int valueOf( ArrayList * list, int element );
int size(ArrayList * list);
int capacity(ArrayList * list);
ArrayList * ArrayList_Init( int n );

int append(ArrayList * list, int val){

	if(list->sz == list->cap){
		list->data = (int*)realloc(list->data,sizeof(int)*list->cap*2);
		list->cap = list->cap*2;
	}
	
	if(list->data == NULL)
		return 1;

	list->data[list->sz] = val;
	(list->sz)++;

	return 0;
}

int print(ArrayList * list){

	int i;

	if(list->sz == 0)
		return 1;

	for(i=0;i<list->sz;i++)
		printf("%d ",list->data[i]);

	printf("\b\n");
	
	return 0;
}

int set(ArrayList * list, int val, int index){

	if(index<0 || index >= list->sz)
		return 1;

	list->data[index] = val;
	return 0;
}

int insert(ArrayList * list, int val, int index){

	if(index<0 || index>= list->sz)
		return 1;

	if(list->sz == list->cap){
		list->data = (int*)realloc(list->data,sizeof(int)*list->cap*2);
		list->cap = list->cap*2;
	}
	
	if(list->data == NULL)
		return 1;

	memmove(&(list->data[index+1]), &(list->data[index]), sizeof(int)*(list->sz - index));
	(list->sz)++;

	return 0;
}

int destroy(ArrayList * list){

	free(list->data);
	free(list);
	return 0;
}

int valueOf(ArrayList * list, int element){
	
	return list->data[element];
}	

int size(ArrayList * list){

	return list->sz;
}

int capacity(ArrayList * list){

	return list->cap;
}

ArrayList * ArrayList_Init( int n ){

	ArrayList *list = (ArrayList*)malloc(sizeof(ArrayList));

	if(n==0)
		list->cap = 1;
	else
		list->cap = n;

	list->sz = n;
	list->data = (int*)malloc(sizeof(int)*list->cap);

	list->append = append;
	list->print = print;
	list->set = set;
	list->insert = insert;
	list->destroy = destroy;
	list->valueOf = valueOf;
	list->size = size;
	list->capacity = capacity;

	return list;
}
int main(void)
{
	int n = 3;
	int i;
	int stat; // Error code
	int size;
	int val = 0;
	int capacity;

	// allocate list
	ArrayList *list = NULL;
	list = ArrayList_Init(n);
	printf("ArrayList initialized to %d elements\n", n);
	printf("Size of List = %d\n", list->size(list));
	printf("Capacity of List = %d\n", list->capacity(list));

	// Fill initial values
	list->set(list, val++, 0);
	list->set(list, val++, 1);
	list->set(list, val++, 2);
	
	// Print List
	stat = list->print(list); // simple display of list contents
	printf("Size of List = %d\n", list->size(list));
	printf("Capacity of List = %d\n", list->capacity(list));
	
	// Test append and auto-resize
	stat = list->append(list,val++) ; // add val to end of the list
	stat = list->print(list); // simple display of list contents
	printf("Size of List = %d\n", list->size(list));
	printf("Capacity of List = %d\n", list->capacity(list));
	
	// Some more appends
	stat = list->append(list,val++) ; // add val to end of the list
	stat = list->append(list,val++) ; // add val to end of the list
	stat = list->print(list); // simple display of list contents
	printf("Size of List = %d\n", list->size(list));
	printf("Capacity of List = %d\n", list->capacity(list));

	// Test insert
	stat = list->insert(list, val++, 1); // insert val into index (increasing ArrayList size by one, and bumping all values over)
	stat = list->print(list); // simple display of list contents
	printf("Size of List = %d\n", list->size(list));
	printf("Capacity of List = %d\n", list->capacity(list));

	// Test insert redux
	stat = list->insert(list, val++, 4); // insert val into index (increasing ArrayList size by one, and bumping all values over)
	stat = list->print(list); // simple display of list contents
	printf("Size of List = %d\n", list->size(list));
	printf("Capacity of List = %d\n", list->capacity(list));

	// Test valueOf
	stat = list->print(list); // simple display of list contents
	printf("list[0] = %d\n", list->valueOf(list,0)) ;//return value of specified element
	printf("list[1] = %d\n", list->valueOf(list,1)) ;//return value of specified element
	
	// Test error handling
	printf("insert error = %d\n", list->insert(list, val++, 1000));
	printf("insert error = %d\n", list->insert(list, val++, -1000));
	printf("set error = %d\n", list->set(list, val++, 1000));
	printf("set error = %d\n", list->set(list, val++, -1000));
	ArrayList * list2 = ArrayList_Init(0);
	stat = list2->print(list2);
	printf("bad print error = %d\n", stat);

	// Test efficiency
	// NOTE - grading script will kill your code if this takes > 3 seconds
	val = 0;
	printf("Efficiency test...\n");
	for( i = 0; i < 100000000; i++ )
		list2->append(list2, val++ );

	// test destroy
	stat = list->destroy(list); //free list memory
	stat = list2->destroy(list2); //free list memory

	return 0;
}
