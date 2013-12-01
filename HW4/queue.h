typedef struct queue{

	void *	data;
	int 	size;
	int 	n_items;
	int	first_item;
	int	item_size;
	int	nq(struct queue * queue, void * item);
	void *	dq(struct queue * queue);
	void *  peek(struct queue * queue);
	int	destroy(struct queue * queue);

} Queue;

int 	q_nq(struct queue * queue, void * item);
void *	q_dq(struct queue * queue);
void *  q_peek(struct queue * queue);
int	q_destroy(struct queue * queue);
Queue * init_q(int size, size_t item_size);
