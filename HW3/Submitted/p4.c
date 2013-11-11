#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum type{CHAR, INT, FLOAT, DOUBLE} Type;

typedef struct array{
  void *vals;          // pointer to your data
  Type type;           // type of data being stored
  int rank;            // number of dimensions (must support 1, 2, and 3)
  int dims[3];         // x, y, z dimensions of the array
} Array;

Array * array_init(int rank, int dims[], Type type); //init new Array
void  array_print(Array * arr); // prints Array
void  arr_fill(Array * arr, void *fill_value); //sets all values to fill_value
void* arr_sum(Array * arr); // sum of all elements in the Array
void* arr_min(Array * arr); // minimum element in the Array
void* arr_max(Array * arr); // maximum element in the Array
void* arr_get(Array * arr, int coords[3] ); 
void arr_set(Array * arr, int coords[3], void * val );
int t_sz(Type type);
void *item_address(Array * arr, int i, int j, int k);
void print_arr_item(Array * arr, int i, int j, int k);

int t_sz(Type type){
	if(type == CHAR)
		return sizeof(char);
	else if (type == INT)
		return sizeof(int);
	else if (type == FLOAT)
		return sizeof(float);
	else if (type == DOUBLE)
		return sizeof(double);
	return -1;
}

Array * array_init(int rank, int dims[], Type type){

	int d1, d2, d3;
	int i;
 
	Array * arr = (Array*)malloc(sizeof(Array));
	if(arr == NULL)
		return arr;

	arr->rank = rank;
	arr->type = type;

	arr->dims[0] = 1;
	arr->dims[1] = 1;
	arr->dims[2] = 1;

	for(i=0;i<rank;i++)
		arr->dims[(3-rank)+i] = dims[i];
	
	d1 = arr->dims[0];
	d2 = arr->dims[1];	
	d3 = arr->dims[2];

	arr->vals = (void*)calloc(d1*d2*d3, t_sz(type));
	
	return arr;
}

void array_print(Array * arr){

	int i, j, k;

	for(i=1;i<=arr->dims[0];i++){
		for(j=1;j<=arr->dims[1];j++){
			for(k=1;k<=arr->dims[2];k++){
				print_arr_item(arr,i,j,k);
				printf(" ");
			}
			printf("\b\n");
		}
		printf("\n");
	}
}

void print_arr_item(Array * arr, int i, int j, int k){

	if(arr->type == CHAR)
		printf("%c", *((char*)(item_address(arr,i,j,k))));
	else if(arr->type == INT)
		printf("%d", *((int*)(item_address(arr,i,j,k))));
	else if(arr->type == FLOAT)
		printf("%.2f", *((float*)(item_address(arr,i,j,k))));
	else if(arr->type == DOUBLE)
		printf("%.2f", *((double*)(item_address(arr,i,j,k))));
}

void *item_address(Array * arr, int i, int j, int k){

	i--;
	j--;
	k--;

	return (void*)( ((char*)(arr->vals))+((i*(arr->dims[1]*arr->dims[2]) + j*(arr->dims[2]) + k) * t_sz(arr->type)));

}

void arr_fill(Array * arr, void *fill_value){

	int i;
	
	for(i=0;i<arr->dims[0]*arr->dims[1]*arr->dims[2];i++){
		memcpy( (void*)(((char*)arr->vals)+(i*t_sz(arr->type))) , fill_value, t_sz(arr->type));
	}
}

void* arr_sum(Array *arr){

	void *sum = calloc(1,t_sz(arr->type));
	void *item;

	int i;

	for(i=0;i<arr->dims[0]*arr->dims[1]*arr->dims[2];i++){
		item = (void*)(((char*)arr->vals)+(i*t_sz(arr->type)));
		if(arr->type == CHAR)
			*((char*)sum) += *((char*)item);
		else if(arr->type == INT)
			*((int*)sum) += *((int*)item);
		else if(arr->type == FLOAT)
			*((float*)sum) += *((float*)item);
		else if(arr->type == DOUBLE)
			*((double*)sum) += *((double*)item);
	}
	return sum;
}

void *arr_min(Array * arr){

	void *min = arr->vals;
	void *item;
	int i;
	
	for(i=0;i<arr->dims[0]*arr->dims[1]*arr->dims[2];i++){
		item = (void*)(((char*)arr->vals)+(i*t_sz(arr->type)));
		if(arr->type == CHAR && *((char*)min) > *((char*)item))
			min = item;
		if(arr->type == INT && *((int*)min) > *((int*)item))
			min = item;
		if(arr->type == FLOAT && *((float*)min) > *((float*)item))
			min = item;
		if(arr->type == DOUBLE && *((double*)min) > *((double*)item))
			min = item;
	}
	
	return min;
}

void *arr_max(Array * arr){

	void *max = arr->vals;
	void *item;
	int i;
	
	for(i=0;i<arr->dims[0]*arr->dims[1]*arr->dims[2];i++){
		item = (void*)(((char*)arr->vals)+(i*t_sz(arr->type)));
		if(arr->type == CHAR && *((char*)max) < *((char*)item))
			max = item;
		if(arr->type == INT && *((int*)max) < *((int*)item))
			max = item;
		if(arr->type == FLOAT && *((float*)max) < *((float*)item))
			max = item;
		if(arr->type == DOUBLE && *((double*)max) < *((double*)item))
			max = item;
	}
	
	return max;
}

void *arr_get(Array * arr, int coords[3]){
	
	int internal_coords[3];
	int i;

	internal_coords[0] = 1;
	internal_coords[1] = 1;
	internal_coords[2] = 1;

	for(i=0;i<arr->rank;i++)
		internal_coords[(3-arr->rank)+i] = coords[i] + 1;

	return item_address(arr, internal_coords[0], internal_coords[1], internal_coords[2]);

}

void arr_set(Array * arr, int coords[3], void * val){
	
	int internal_coords[3];
	int i;

	internal_coords[0] = 1;
	internal_coords[1] = 1;
	internal_coords[2] = 1;

	for(i=0;i<arr->rank;i++)
		internal_coords[(3-arr->rank)+i] = coords[i] + 1;

	memcpy(item_address(arr, internal_coords[0], internal_coords[1], internal_coords[2]), val, t_sz(arr->type));

}
