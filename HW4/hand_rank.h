#ifndef HAND_RANK_H
#define HAND_RANK_H

typedef struct hand_rank {

	long key;
	char *desc;
	double cumulative_prob;
	unsigned short rank;

} Hand_rank;

Hand_rank * import_rank_data(void);
int hand_rank_comp(const void *key, const void *datum);
long hand_key(Hand * hand);
short prime_val(Card card);
Hand_rank * rank_hand(Hand hand, Hand_rank * rank_data); 
#endif
