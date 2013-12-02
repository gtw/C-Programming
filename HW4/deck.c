#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

int card_comp(const void *a, const void *b){

	Card * ai = (Card*)a;
	Card * bi = (Card*)b;

	if(ai->val != bi->val)
		return((ai->val < bi->val) - (ai->val > bi->val));
	else
		return((ai->suit < bi->suit) - (ai->suit > bi->suit));

}
 
int hand_sort(Hand * hand){

	qsort(hand->cards, hand->size, sizeof(Card), card_comp);
	return 0;

}

int val_print(Val val){

	if(val<9 && val>-1)
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

Card hand_remove(Hand * hand, int n){

	Card return_card;

	if(n > hand->cards_in_hand){
		return_card.val = ERR_V;
		return_card.suit = ERR_S;
		return return_card;
	}

	return_card = hand->cards[n-1];
	
	if(n < hand->size)
		memcpy(&((hand->cards)[n-1]), &((hand->cards)[n]), sizeof(Card) * ((hand->size - n) + 1));
	
	hand->cards[hand->size - 1].val = ERR_V;
	hand->cards[hand->size - 1].suit = ERR_S;

	hand->cards_in_hand--;

	return return_card;
}

int hand_add(Hand * hand, Card card){

	if(hand->cards_in_hand == hand->size){
		printf("Hand already full, card has not been added\n");
		return 1;
	}
	
	if(card.val == ERR_V || card.suit == ERR_S){
		printf("Cannot add blank card to hand\n");
		return 1;
	}	

	hand->cards[hand->cards_in_hand] = card;
	hand->cards_in_hand++;

	return 0;
} 
	 
Hand * hand_init(int ncards){

	int i;

	Hand * new_hand = (Hand*)malloc(sizeof(Hand));
	
	new_hand->size          = ncards;
	new_hand->cards_in_hand = 0;
	new_hand->cards         = (Card*)malloc(sizeof(Card)*ncards);
	new_hand->sort          = hand_sort;
	new_hand->print         = hand_print;	
	new_hand->destroy       = hand_destroy;
	new_hand->add		= hand_add;
	new_hand->remove	= hand_remove;

	for(i=0; i<ncards; i++){
		new_hand->cards[i].val = ERR_V;
		new_hand->cards[i].suit = ERR_S;
	}

	return new_hand;
}

int deck_realign(Deck * deck){

	return deck->cards->realign(deck->cards);

}

int deck_shuffle(Deck * deck){

	int i, j;
	Card * d = (Card*)(deck->cards->data);
	Card * buffer = (Card*)malloc(sizeof(Card));

	deck->realign(deck);
	
	for(j = (deck->cards->n_items) - 1; j>0; j--){
		i = rand()%(j+1);
		memcpy(buffer, &(d[i]), sizeof(Card));
		memcpy(&(d[i]), &(d[j]), sizeof(Card)); 				
		memcpy(&(d[j]), buffer, sizeof(Card)); 				
	}

	free(buffer);

	return 0;
}

int deck_destroy(Deck * deck){

	deck->cards->destroy(deck->cards);
	free(deck);
	return 0;
}

int deck_print(Deck * deck){

	int i;

	deck->realign(deck);
	
	for(i=0;i<deck->cards->n_items;i++){
		val_print( (((Card*)(deck->cards->data))[i]).val);
		suit_print( (((Card*)(deck->cards->data))[i]).suit);
		printf(" ");
	}
	printf("\n");

	return 0;
}

Card deck_pick_card(Deck * deck){

	return *((Card*)(deck->cards->dq(deck->cards)));

}

int deck_return_card(Deck * deck, Card card){

	return deck->cards->nq(deck->cards, &card);

}

Deck * init_deck(int size, Deck * src_deck, int std_fill){
	
	int i, j;
	Card add_card;
	Deck * deck = (Deck*)malloc(sizeof(Deck));
	if(deck==NULL){
		free(deck);
		return NULL;
	}

	if(src_deck == NULL){
	
		deck->cards = init_q(size, sizeof(Card));

		deck->realign     = deck_realign;
		deck->shuffle     = deck_shuffle;
		deck->destroy     = deck_destroy;
		deck->print       = deck_print;
		deck->pick_card   = deck_pick_card;
		deck->return_card = deck_return_card;
		
		if(std_fill == 1 && size == 52){
			for(i=0;i<4;i++){
				add_card.suit = i;
				for(j=0;j<13;j++){
					add_card.val = j;
					deck->return_card(deck,add_card);
				}
			}
		}	
	}

	else{
		memcpy(deck, src_deck, sizeof(Deck));
		deck->cards->data = (void*)malloc(sizeof(Card)*src_deck->cards->size);
		memcpy(deck->cards->data, src_deck->cards->data, sizeof(Card)*src_deck->cards->size);
	}

	return deck;
}
