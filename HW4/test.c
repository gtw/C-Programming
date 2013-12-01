#include "deck.h"

int card_comp(const void *a, const void *b){

	Card * ai = (Card*)a;
	Card * bi = (Card*)b;

	if(ai->val != bi->val)
		return((ai->val > bi->val) - (ai->val < bi->val));
	else
		return((ai->suit > bi->suit) - (ai->suit < bi->suit));

}
 
int hand_sort(Hand * hand){

	qsort(hand->cards, hand->ncards, sizeof(Card), card_comp);
	return 0;

}

int val_print(Val val){

	if(val<9)
		printf("%d",val+2);
	else if(val==J)
		printf("J");
	else if(val==Q)
		printf("Q");
	else if(val==K)
		printf("K");
	else if(val==A)
		printf("A");
	else
		return 1;

	return 0;

}

int suit_print(Suit suit){

	if(suit == CLUBS)
		printf("♣");
	else if (suit == DIAMONDS)
		printf("♦");
	else if (suit == HEARTS)
		printf("♥");
	else if (suit == SPADES)
		printf("♠");
	else
		return 1;

	return 0;

} 
int hand_print(Hand * hand){

	int i;
	
	for(i=0;i<hand->ncards;i++){
		val_print((hand->cards)[i].val);
		suit_print((hand->cards)[i].suit);
		printf(" ");
	}

	printf("\n");

	return 0;
}

int hand_destroy(Hand * hand){

	free(hand->cards);
	free(hand);
	return 0;
}

Hand * hand_init(int ncards){

	Hand * new_hand = (Hand*)malloc(sizeof(Hand));
	
	new_hand->ncards = ncards;
	new_hand->cards  = (Card*)malloc(sizeof(Card)*ncards);
	new_hand->sort   = hand_sort;
	new_hand->print  = hand_print;	
	new_hand->destroy = hand_destroy;

	return new_hand;
}


int main(int argc, char *argv[]){

	int i;
	Hand * new_hand = hand_init(5);	

	for(i=0;i<5;i++){
		new_hand->cards[i].val = i;
		new_hand->cards[i].suit = HEARTS;
	}

	new_hand->print(new_hand);

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

