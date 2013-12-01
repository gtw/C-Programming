#ifndef DECK_H
#define DECK_H

typedef enum suit{

	CLUBS,
	DIAMONDS,
	HEARTS,
	SPADES

} Suit;

int suit_print(Suit suit);

typedef enum val {

	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	_10,
	J,
	Q,
	K,
	A

} Val;
 	
int val_print(Val val);

typedef struct card {

	Suit 	suit;
	Val	val;

} Card;

int card_comp(const void *a, const void *b);

typedef struct hand {

	Card * 	cards;
	int	size;
	int 	cards_in_hand;
	int	(*sort)(struct hand * hand);
	int	(*print)(struct hand * hand);
	int	(*destroy)(struct hand * hand);	
	int	(*add)(struct hand * hand, Card * card);
	Card *	(*remove)(struct hand * hand, int n);
} Hand;

int 	hand_sort(Hand * hand);
int 	hand_print(Hand * hand);
int 	hand_destroy(Hand * hand);
int 	hand_add(struct hand * hand, Card * card);
Card *	hand_remove(struct hand * hand, int n);
Hand * 	hand_init(int ncards);

typedef struct deck{

	Queue  	cards;
	int 	(*realign)(struct deck * deck);
	int 	(*shuffle)(struct deck * deck);
	int 	(*destroy)(struct deck * deck);
	int 	(*print)(struct deck * deck);
	Card *	(*pick_card)(struct deck * deck);
	int 	(*return_card)(struct deck * deck, Card * card);

} Deck;

int 	deck_realign(Deck * deck);
int 	deck_shuffle(Deck * deck);
int 	deck_destroy(Deck * deck);
int 	deck_print(Deck * deck);
Card *	deck_pick_card(struct deck * deck);
int 	deck_return_card(struct deck * deck, Card * card);
Deck *	init_deck(int size, Deck * src_deck, int std_fill);
#endif
