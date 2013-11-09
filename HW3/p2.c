#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	int indexFrom;
	int indexTo;
} MapEntry;

typedef MapEntry * Map;

int permute(void *data, int nblobs, size_t szblob, Map map);
void print_blobs(int *my_blobs, int nblobs);
int verify(Map map, int size);
int mapsort(const void *a, const void *b);
void pre_process(void *data, int nblobs, size_t szblob, Map map);
void printMap(Map map, int size);

int main(int argc, char *argv[]){

	int nblobs = 10;
	int *my_blobs = (int*)malloc(sizeof(int)*nblobs);
	int i;
	Map map = (Map) malloc( sizeof(MapEntry) * nblobs );
	
	for(i=0;i<nblobs;i++){
		my_blobs[i] = 10+i;
	}

	map[0].indexFrom = 0;
	map[0].indexTo = 4;
	map[1].indexFrom = 4;
	map[1].indexTo = 1;
	map[2].indexFrom = 3;
	map[2].indexTo = 0;
	map[3].indexFrom = 0;
	map[3].indexTo = 3;
	map[4].indexFrom = 1;
	map[4].indexTo = 2;
	map[5].indexFrom = 2;
	map[5].indexTo = 5;
	map[6].indexFrom = 2;
	map[6].indexTo = 6;
	map[7].indexFrom = 2;
	map[7].indexTo = 7;
	map[8].indexFrom = 2;
	map[8].indexTo = 8;
	map[9].indexFrom = 9;
	map[9].indexTo = 9;

	print_blobs(my_blobs, nblobs);
	permute(my_blobs, nblobs, sizeof(int), map);
	print_blobs(my_blobs, nblobs);
	return 0;
}

int permute(void *data, int nblobs, size_t szblob, Map map){

	int i;
	int *used_command = (int*)calloc(nblobs, sizeof(int));
	void *temp = (void*)malloc(szblob);
	int current_index;
	int first_to;

	char* d = (char*)data;

	if(verify(map,nblobs)==-1){
		return -1;
	}
	
	pre_process(data, nblobs, szblob, map);		
	qsort(map, nblobs, sizeof(MapEntry), mapsort);	
	
	for(i=0;i<nblobs;i++){
		
		if(used_command[i] == 1)
			continue;
	
		first_to = map[i].indexTo;
		
		memcpy(temp, d + (map[i].indexTo * szblob), szblob);
		memcpy(d + (map[i].indexTo * szblob), d + (map[i].indexFrom * szblob), szblob);
		used_command[i] = 1;
		current_index = map[i].indexFrom;

		while(map[current_index].indexFrom != first_to){

			memcpy(d+(map[current_index].indexTo * szblob), d+(map[current_index].indexFrom * szblob), szblob);
			used_command[current_index] = 1;
			current_index = map[current_index].indexFrom;

		}

		memcpy(d + (map[current_index].indexTo * szblob), temp, szblob);
		used_command[current_index] = 1;
	}

	return 0;
}

int mapsort(const void *a, const void *b){

	MapEntry *ai = (MapEntry*)a;
	MapEntry *bi = (MapEntry*)b;
	int a_to = ai->indexTo;
	int b_to = bi->indexTo;

	return ( (a_to > b_to) - (a_to < b_to) );
}

void pre_process(void *data, int nblobs, size_t szblob, Map map){

	int *from_count = (int*)calloc(nblobs, sizeof(int));
	int i, j, k;
	int open_count = 0;
	int *open_indexes;
	int current_open = 0;
	char *d = (char*)data;

	for(i=0;i<nblobs;i++){
		(from_count[map[i].indexFrom])++;
		if(from_count[map[i].indexFrom]>=2){
			open_count++;
		}
	}

	if(open_count == 0)
		return;
	
	open_indexes = (int*)malloc(sizeof(int)*open_count);

	for(i=0;i<nblobs;i++){
		if(from_count[i] == 0){
			open_indexes[current_open] = i;
			current_open++;
		}
	}

	current_open = 0;

	for(i=0;i<nblobs;i++){
		k = 0;
		j = 0;
		while(k<from_count[i]-1){
			if(map[j].indexFrom == i){
				memcpy( d+(open_indexes[current_open] * szblob),  d+(map[j].indexFrom * szblob), szblob);
				map[j].indexFrom = open_indexes[current_open]; 
				current_open++;
				k++;
			}
			j++;
		}
	}
}
	

void printMap(Map map, int size){
	int i;
	for(i=0;i<size;i++)
		printf("[%d,%d] ", map[i].indexFrom, map[i].indexTo);
	printf("\n");
}

int verify(Map map, int size){

	int i;
	int *count = (int*)malloc(sizeof(int)*size);
	
	for(i=0;i<size;i++)
		count[i] = 0;
	
	for(i=0;i<size;i++){
		(count[map[i].indexTo])++;
		if(count[map[i].indexTo]>1)
			return -1;
	}
	return 0;
}



void print_blobs(int *my_blobs, int nblobs){

	int i;
	printf("( ");
	for(i=0;i<nblobs;i++){
		printf("%d ", my_blobs[i]);
	}
	printf(")\n");
}
