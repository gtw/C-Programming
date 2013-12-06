#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "deck.h"
#include "hand_rank.h"

int main(int argc, char *argv[]){

	int i;

	Hand_rank * poker_hands = import_rank_data();

	Hand * hand_a = hand_init(5);
	Hand * hand_b = hand_init(5);	
	Deck * deck = init_deck(52,NULL,1);

	srand(time(NULL));
	
	deck->shuffle(deck);

	for(i=0; i<5; i++){
		hand_a->add(hand_a, deck->pick_card(deck));
		hand_b->add(hand_b, deck->pick_card(deck));
	}

	hand_a->print(hand_a);
	printf("%s %f\n",rank_hand(hand_a, poker_hands)->desc, rank_hand(hand_a, poker_hands)->cumulative_prob);
	hand_b->print(hand_b);
	printf("%s %f\n",rank_hand(hand_b, poker_hands)->desc, rank_hand(hand_b, poker_hands)->cumulative_prob);
/*
	deck->print(deck);
*/	hand_a->destroy(hand_a);
	hand_b->destroy(hand_b);
	deck->destroy(deck);
	free(poker_hands);

	return 0;
}

/* 
 _________
/Q        \  
|    _    |
|  _( )_  | 
| (     ) |
|   ) (   |
|         |
\________Q/
 _________
/         \
|2  _  _  |
|  ( \/ ) |
|   \  /  |
|    \/   |
|        2|
\_________/
 _________
/	  \
|         |
|   / \   |
|  (   )  |
|   \ /   |
|         |
\_________/
 _________
/         \
|    .    |
|   / \   |
|  (   )  |
|    I    | 
|         |
\_________/
*/

