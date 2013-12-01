#include <stdio.h>
#include "deck.h"

int main(int argc, char *argv[]){

	int i;
	Hand * new_hand = hand_init(13);	
	Deck * deck = deck_init(52,NULL,1);

	for(i=0;i<13;i++){
		new_hand->cards[i].val = i;
		new_hand->cards[i].suit = HEARTS;
	}

	new_hand->print(new_hand);

	deck->print(deck);
	deck->shuffle(deck);
	deck->print(deck);
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

