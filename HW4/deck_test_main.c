#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "deck.h"

int main(int argc, char *argv[]){

	int i;

	Hand * hand_a = hand_init(5);
	Hand * hand_b = hand_init(5);	
	Deck * deck = init_deck(52,NULL,1);

	srand(time(NULL));
	
	deck->shuffle(deck);
	deck->print(deck);

	for(i=0; i<6; i++){
		hand_a->add(hand_a, deck->pick_card(deck));
		hand_b->add(hand_b, deck->pick_card(deck));
	}

	hand_a->print(hand_a);
	hand_b->print(hand_b);

	deck->print(deck);
	hand_a->destroy(hand_a);
	hand_b->destroy(hand_b);
	deck->destroy(deck);

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

