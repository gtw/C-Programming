#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int q_nq(Queue * queue, void * item){

        if(queue->n_items >= queue->size){
                printf("Queue is filled.  Item has not been added to queue\n");
                return -1;
        }

        memcpy( ((char*)(queue->data)) + (queue->item_size * ((queue->n_items + queue->first_item)%queue->size)), item, queue->item_size);

        (queue->n_items)++;
        
        return 0;
} 

void * q_dq(Queue * queue){

        void * dq_item;

        if(queue->n_items == 0){
                printf("Queue is empty.  Item has not been removed from the queue\n");        
                return NULL;
        }

        dq_item = (void*)malloc(queue->item_size);
        memcpy(dq_item, ((char*)(queue->data)) + (queue->item_size * queue->first_item), queue->item_size);
        memset( ((char*)(queue->data)) + (queue->item_size * queue->first_item), 0, queue->item_size);
        queue->first_item = (queue->first_item + 1)%(queue->size);
        queue->n_items--;
        
        return dq_item;
}

void * q_peek(Queue * queue){

        void * peek_item;

        if(queue->n_items == 0){
                printf("Queue is empty.  No items to peek from the queue\n");
                return NULL;
        }

        peek_item = (void*)malloc(queue->item_size);
        memcpy(peek_item, ((char*)(queue->data)) + (queue->item_size * queue->first_item), queue->item_size);
        
        return peek_item;
}

int q_destroy(Queue * queue){

        free(queue->data);
        free(queue);

        return 0;
}                

int q_realign(Queue * queue){

	void * buffer;
	if(queue->first_item == 0)
		return 0;

	buffer = (void*)malloc(queue->item_size * queue->first_item);
	memcpy(buffer, queue->data, queue->item_size * queue->first_item);
	memmove(queue->data, ((char*)(queue->data)) + (queue->item_size * queue->first_item), queue->item_size * (queue->size - queue->first_item));
	memcpy( ((char*)(queue->data)) + (queue->item_size * (queue->size - queue->first_item)), buffer, queue->item_size * queue->first_item );

	queue->first_item = 0;
	return 0;
}

Queue * init_q(int size, size_t item_size){

        Queue * queue = (Queue*)malloc(sizeof(Queue));
        
        queue->data             = (void*)malloc(size * item_size);
        queue->size             = size;
        queue->n_items          = 0;
        queue->first_item       = 0;
        queue->item_size        = item_size;
        queue->nq               = q_nq;
        queue->dq               = q_dq;
        queue->peek             = q_peek;
        queue->destroy		= q_destroy;
	queue->realign		= q_realign;	
	
	return queue;
}
