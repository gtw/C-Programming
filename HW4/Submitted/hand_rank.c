#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hand_rank.h"
#include "deck.h"

/* 	Imports the table storing information on hand values.  See readme for detailed description
	of how this table was compiled and how it is used. */

Hand_rank * import_rank_data(void){

	int i;
	char key[20];
	char cumulative_prob[20];
	char rank[10];

	FILE *hands_file;
	Hand_rank * poker_hands = (Hand_rank*)malloc(sizeof(Hand_rank)*7462);
	
	hands_file = fopen("poker_hands.txt", "r");

	for(i=0;i<7462;i++){
		poker_hands[i].desc = calloc(26,sizeof(char));
		fscanf(hands_file, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", key, poker_hands[i].desc, cumulative_prob, rank);
		poker_hands[i].key = atol(key);
		poker_hands[i].cumulative_prob = atof(cumulative_prob);
		poker_hands[i].rank = atoi(rank);
	}
	
	return poker_hands;
}

/*	Creates a "key" for a given hand in the game to perform a look-up from the hand_rank data. */

long get_hand_key(Hand * hand){

	long key = 1;
	int flush = -1;
	int i;

	for(i=0;i<hand->size;i++){
		key *= prime_val(hand->cards[i]);
		if(i>0){
			if(hand->cards[i].suit != hand->cards[i-1].suit){
				flush = 1;
			}
		}	
			
	}

	
	return key*flush;
}

/*	Read the readme to understand the assignment of primes in more detail.  The use of primes
	to represent the different face cards is crucial to the functioning of this table and allows
	this process to be performed without sorting the hand prior to lookup  */

short prime_val(Card card){

	switch(card.val){

		case _2: return 2; break;
		case _3: return 3; break;
		case _4: return 5; break;
		case _5: return 7; break;
		case _6: return 11; break;
		case _7: return 13; break;
		case _8: return 17; break;
		case _9: return 19; break;
		case _10: return 23; break;
		case J: return 29; break;
		case Q: return 31; break;
		case K: return 37; break;
		case A: return 41; break;
		default: return 0;

	}
	return 0;
}

/*	The comparison function running underneath the bsearch call in "rank_hand".  Note the first
	object passed is the address of a hand key stored from the output of "get_hand_key" while
	the second is the address of a "hand_rank" object which contains information about a given
	hand in poker, including its key. */

int hand_rank_comp(const void *hand_key, const void *hand_rank){

	long hand_k = *((long*)hand_key);
	long hand_rank_k = ((Hand_rank*)hand_rank)->key;

	return ((hand_k > hand_rank_k) - (hand_k < hand_rank_k));
}

/*	The user interface for the hand_rank module.  The function searches the hand rank data for the
	hand_rank object associated with a given "key" generated for a hand and returns a pointer to that
	hand_rank object.  This pointer can be dereferenced by the user to examine the hand_rank object's
	different members.  Sometimes the user will just want the relative ranking of this class of hand
	while at other times they will want a description of the hand or its place in the CDF.  All this
	information is stored in the related hand_rank object returned. */

Hand_rank * rank_hand(Hand * hand, Hand_rank * rank_data){

	long hand_key = get_hand_key(hand);
	return bsearch(&hand_key, rank_data, 7462, sizeof(Hand_rank), hand_rank_comp);

}
