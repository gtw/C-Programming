#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

/*	Card comp function used in sorts, searches, and other comparisons 
	Sorts in descending rather than ascending order */

int card_comp(const void *a, const void *b){

	Card * ai = (Card*)a;
	Card * bi = (Card*)b;

	if(ai->val != bi->val)
		return(bi->val - ai->val);
	else
		return(bi->suit - ai->suit);

}

/*	Sort function for hands of cards */
 
int hand_sort(Hand * hand){

	qsort(hand->cards, hand->size, sizeof(Card), card_comp);
	return 0;

}

/*	Prints a card's value */

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
	else if(val==ERR_V)
		printf("[");
	else
		return 1;

	return 0;

}

/*	Function to print a card's suit */

int suit_print(Suit suit){

	if(suit == CLUBS)
		printf("♣");
	else if (suit == DIAMONDS)
		printf("♦");
	else if (suit == HEARTS)
		printf("♥");
	else if (suit == SPADES)
		printf("♠");
	else if (suit == ERR_S)
		printf("]");
	else
		return 1;

	return 0;

}

/*	Function to print a hand of cards */
 
int hand_print(Hand * hand){

	int i;
	
	for(i=0;i<hand->size;i++){
		val_print((hand->cards)[i].val);
		suit_print((hand->cards)[i].suit);
		printf(" ");
		if(hand->cards[i].val != _10)
			printf(" ");
	}

	printf("\n");

	return 0;
}

/*	Simple destroy function for hands */

int hand_destroy(Hand * hand){

	free(hand->cards);
	free(hand);
	return 0;
}

/*	Removes the nth card in the hand (note that n = 1 and not n = 0 will remove
	the first card in the hand).  There is first a check that the index requested
	contains a non-blank card.  If not, the blank card is returned.  Once a card
	is removed from the hand the user has the option of sorting the hand (hence
	realigning it) or not.  Sorting is highly recommended and would only not
	be done in instances where a number of cards were to be removed and so
	original locations would need to be preserved until the final card had been
	removed */

Card hand_remove(Hand * hand, int n, int sort_ind){

	Card return_card;

	if(n > hand->cards_in_hand){
		return_card.val = ERR_V;
		return_card.suit = ERR_S;
		return return_card;
	}

	return_card = hand->cards[n-1];
	
	hand->cards[n - 1].val = ERR_V;
	hand->cards[n - 1].suit = ERR_S;

	hand->cards_in_hand--;
	
	if(sort_ind == 1){
		hand->sort(hand);
	}

	return return_card;
}

/*	Checks if hand is already full, and if not, adds the card supplied to the
	first empty spot in the hand.  Note that cards are always kept so that open
	spaces are at the end of the array storying them.  There is a check as well
	that blank cards are not being added to hands. */

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

/*	Hands are essentially just arrays with associated functions to manipulate
	them, so this initializtion is fairly straightforward.  I malloc space
	for the hand and its cards (size of hand indicate by calling function) and
	then initialize all the card values to the blank card, indicated by
	val = "ERR_V" and suit = "ERR_S";  It is returned as a pointer */
	 
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
/*	Wrapper function for the realign function of the queue object type */

int deck_realign(Deck * deck){

	return deck->cards->realign(deck->cards);

}

/* 	Simple Card Swapper.  You need to pass in your own
	buffer region to avoid constant malloc/freeing */

void card_swap(Card *card_a, Card *card_b, Card * buffer){
	
	memcpy(buffer, card_a, sizeof(Card));
	memcpy(card_a, card_b, sizeof(Card)); 				
	memcpy(card_b, buffer, sizeof(Card)); 				
}

/*	Simply O(n) algorithm that shuffles the deck.  Relies on the fact that
	the underlying data structure is an array. Random numbers between
	0 and the total number of cards in the deck are generated.  Then the
	last card in the deck is switched with a random element with an address lower
	than or possibly equal to its own (i.e. no switching occurs). The process
	is repeated with the second-to-last, third-to-last cards and so on until the
	beginning of the deck is reached.  Source of this algorithm is the following
	Wikipedia article which describes the "Fisher-Yates Shuffle"

	http://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
*/

int deck_shuffle(Deck * deck){

	int i, j;
	Card * d = (Card*)(deck->cards->data);
	Card * buffer = (Card*)malloc(sizeof(Card));

	deck->realign(deck);
	
	for(j = (deck->cards->n_items) - 1; j>0; j--){
		i = rand()%(j+1);
		card_swap(&(d[i]), &(d[j]), buffer);
	}

	return 0;
}

/*	Simple destroy method for the deck.  Calls the queue's destroy function
	for the queue of cards themselves
*/

int deck_destroy(Deck * deck){

	deck->cards->destroy(deck->cards);
	free(deck);
	return 0;
}

/*	This function realigns the deck and then prints the suit and value
	for each card in the deck, in the order in which it would be possible
	to dequeue them. Does not get used in gameplay but was necessary in 
	development
*/

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

/*	Just a wrapper function for the queue object's dequeue function.
	Note I have to cast the object returned as a card, since the
	dequeue function just returns a void pointer, but in this instance
	I know it is returning the address of a card which I want to pass
	return by value.
*/

Card deck_pick_card(Deck * deck){

	return *((Card*)(deck->cards->dq(deck->cards)));

}

/* 	Just a wrapper function for the enqueue, here used for cards */

int deck_return_card(Deck * deck, Card card){

	return deck->cards->nq(deck->cards, &card);

}

/* 	Used to initialize a new deck.  User must provide the size of the deck.
	There is the option to create a copy of a pre-existing deck, called the
	src_deck.  If this option is not taken there is the choice to either
	create a blank deck, or if no source deck is indicated and the size of
	the deck is 52 cards you can populate the deck with the standard 52
	card deck by setting the std_fill option to "1";
*/

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

/*	This function is used to remove a given set of cards from a pre-existing deck.
	It is called prior to the Monte-Carlo simulation to create a 47 card hand not
	including the cards already in the player's hand
*/
	
int	deck_remove_cards(Deck * deck, Card * remove_cards, int n){

	int i;
	int j;
	int card_to_be_removed;

	Card test_card;
	Queue * new_deck = init_q(deck->cards->size, sizeof(Card));
	
	if(new_deck == NULL)
		return -1;

	deck->realign(deck);
	
	for(i=0; i<deck->cards->size; i++){
		test_card = deck->pick_card(deck);
		card_to_be_removed = 0;
		for(j=0; j < n; j++){
			if(card_comp(&test_card, remove_cards+j)==0){
				card_to_be_removed = 1;
				break;
			}
		}

		if(card_to_be_removed == 0){
			new_deck->nq(new_deck, &test_card);
		}
		
	}

	deck->cards->destroy(deck->cards);
	deck->cards = new_deck;
	
	return 0;
}
