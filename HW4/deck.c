#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	qsort(hand->cards, hand->size, sizeof(Card), card_comp);
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
	
	for(i=0;i<hand->size;i++){
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
	
	new_hand->size          = ncards;
	new_hand->cards_in_hand = 0;
	new_hand->cards         = (Card*)malloc(sizeof(Card)*ncards);
	new_hand->sort          = hand_sort;
	new_hand->print         = hand_print;	
	new_hand->destroy       = hand_destroy;

	return new_hand;
}

int deck_realign(Deck * deck){

	return deck->cards->realign(deck->cards);

}

int deck_shuffle(Deck * deck){

	int i, j;

	Card * buffer = (Card*)malloc(sizeof(Card));

	deck->cards.realign(deck->cards);
	
	for(j=deck->cards.n_items, j>0; j--){
		i = rand()%j;
		memcpy(buffer, ((char*)(deck->cards.data)) + (sizeof(Card) * i), sizeof(Card));
		memcpy( ((char*)(deck->cards.data)) + (sizeof(Card) * i), ((char*)(deck->cards.data)) + (sizeof(Card) * j), sizeof(Card)); 				
		memcpy( ((char*)(deck->cards.data)) + (sizeof(Card) * j), buffer, sizeof(Card));
	}

	free(buffer);

	return 0;
}
