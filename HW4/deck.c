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

int deck_destroy(Deck * deck){

	deck->cards.destroy(deck->cards);
	free(deck);
	return 0;
}

int deck_print(Deck * deck){

	int i;

	deck->realign(deck);
	
	for(i=0;i<deck->cards.n_cards;i++){
		val_print( (((Card*)(deck->cards.data))[i]).val);
		suit_print( (((Card*)(deck->cards.data))[i]).suit);
	}
	printf("\n");
}

Card * deck_pick_card(Deck * deck){

	return deck->cards.dq(&(deck->cards));

}

Card * deck_return_card(Deck * deck, Card * card){

	return deck->cards.nq(&(deck->cards), (void*)card);

}

Deck * init_deck(int size, Deck * src_deck, int std_fill){
	
	int i, j;
	Card *  add_card;
	Deck * deck = (Deck*)malloc(sizeof(Deck));
	if(deck==NULL)
		return NULL;

	if(std_deck == NULL){
	
		deck->cards = init_q(size, sizeof(Card));

		deck->realign     = deck_realign;
		deck->shuffle     = deck_shuffle;
		deck->destroy     = deck_destroy;
		deck->print       = deck_print;
		deck->pick_card   = deck_pick_card;
		deck->return_card = deck_return_card;
		
		if(std_fill == 1 && size == 52){
			for(i=0;i<4;i++){
				add_card->suit = i;
				for(j=0;j<13;j++){
					add_card->val = j;
					deck->cards.return_card(deck->cards,add_card);
				}
			}
		}	
	}

	else{
		memcpy(deck, src_deck, sizeof(Deck));
		deck->cards.data = (void*)malloc(sizeof(Card)*src_deck->cards.size);
		memcpy(deck->cards.data, src_deck->cards.data, sizeof(Card)*src_deck->cards.size);
	}

	return deck;
}
