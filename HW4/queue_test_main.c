#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int main(int argc, char * argv[]){

	Queue * int_q = init_q(10, sizeof(int));
	int * add_item;
	int * remove_item;
	int i;

	printf("Trying to dequeue item before adding it.\n");
	remove_item = int_q->dq(int_q);
	free(remove_item);

	printf("Enqueuing element.\n");
	add_item = (int*)malloc(sizeof(int));
	*add_item = 4;
	int_q->nq(int_q,(void*)add_item);

	printf("Trying to dequeue item, should be equal to 4.\n");
	remove_item = int_q->dq(int_q);
	printf("%d\n",*remove_item);
	free(remove_item);
	
	printf("Adding 11 elements to queue, should crash on the 11th.\n");

	for(i=0;i<11;i++){
		printf("%d\n",i);
		*add_item = i;
		int_q->nq(int_q,(void*)add_item);
	}

	printf("Removing elements and ensuring n_items and start shirft correctly.\n");

	int_q->dq(int_q);
	int_q->dq(int_q);

	printf("Int_q's n_items should be 8: %d\n and its start should be 3: %d\n",int_q->n_items,int_q->first_item);

	printf("Current values in Queue\n\n");
	for(i=0;i<10;i++){
		printf("%d ", ((int*)(int_q->data))[i]);
	}
	printf("\n");
	return 0;
}	

