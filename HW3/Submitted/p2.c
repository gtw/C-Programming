#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	int indexFrom;
	int indexTo;
} MapEntry;

typedef MapEntry * Map;

int permute(void *data, int nblobs, size_t szblob, Map map);
int verify(Map map, int size);
int mapsort(const void *a, const void *b);
void pre_process(void *data, int nblobs, size_t szblob, Map map);

/* My permute function requires every index of the data to only be written from
and to a single time.  Since that will not always necessarily be the case my
pre_process function is called to convert the map and underlying data into a
map of this sort.  It can do this using the following fact.  If an index is 
written to multiple indexes, then there exists a corresponding number of indexes
that are never written to another index.  Therefore we can make copies of the
data at the index which is written multiple times, and change corresponding map 
entries to write from the index copied to.  Once this is completed my algorithm 
relies on the fact that the map is now comprised of one or more cycles.  Therefore
I can drop into one of these cycles and then, using my own free space of memory,
follow the cycle around copying data forwards through it.  The way my code is written
I mark every instruction after it is used so that I can be sure that I do not 
navigate a cycle more than once.  By checking every instruction, I can make sure 
I follow every cycle and so have properly implemented the permutation */

int permute(void *data, int nblobs, size_t szblob, Map map){

	int i;
	int *used_command = (int*)calloc(nblobs, sizeof(int));
	void *temp = (void*)malloc(szblob);
	int current_index;
	int first_to;

	char* d = (char*)data;

	if(verify(map,nblobs)==-1){
		free(temp);
		free(used_command);
		return -1;
	}
	
	pre_process(data, nblobs, szblob, map);	
	/* Following the pre_process step, all indexes are written to
	a single time.  We can sort them in order, and the instruction  at every 
	index in map will be the one that writes to that index in the data. */
	qsort(map, nblobs, sizeof(MapEntry), mapsort);	
	
	for(i=0;i<nblobs;i++){
		
		if(used_command[i] == 1)
			continue;
	
		first_to = map[i].indexTo;
		
		memcpy(temp, d + (map[i].indexTo * szblob), szblob);
		memcpy(d + (map[i].indexTo * szblob), d + (map[i].indexFrom * szblob), szblob);
		used_command[i] = 1;
		/* Since my map is sorted, this instruction takes me to the map entry
		that writes to the previous entry in the cycle I'm currently in */
		current_index = map[i].indexFrom;

		while(map[current_index].indexFrom != first_to){

			memcpy(d+(map[current_index].indexTo * szblob), d+(map[current_index].indexFrom * szblob), szblob);
			used_command[current_index] = 1;
			current_index = map[current_index].indexFrom;

		}

		memcpy(d + (map[current_index].indexTo * szblob), temp, szblob);
		used_command[current_index] = 1;
	}
	free(temp);
	free(used_command);
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

	/* Populates an array counting how many times an index is written from
	Every time an index is written from more than once we increment a counter
	of the corresponding number of indexes that are never written*/
	for(i=0;i<nblobs;i++){
		(from_count[map[i].indexFrom])++;
		if(from_count[map[i].indexFrom]>=2){
			open_count++;
		}
	}
	/* If no index is copied multiple times terminate*/
	if(open_count == 0){
		free(from_count);	
		return;
	}
	open_indexes = (int*)malloc(sizeof(int)*open_count);
	/*Fill an array with the indexes that are "open", i.e. never copied*/
	for(i=0;i<nblobs;i++){
		if(from_count[i] == 0){
			open_indexes[current_open] = i;
			current_open++;
		}
	}

	current_open = 0;
	/*Copy data moved multiple times into "open indexes" and change correspoindimap entries*/
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
	free(open_indexes);
	free(from_count);	
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
	free(count);
	return 0;
}
