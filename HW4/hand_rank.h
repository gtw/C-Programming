#ifndef HAND_RANK_H
#define HAND_RANK_H

typedef struct hand_rank {

	long key;
	char *desc;
	double cumulative_prob;
	unsigned short rank;

} Hand_rank;
#endif
