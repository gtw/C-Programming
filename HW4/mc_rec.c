#include <stdlib.h>
#include "mc_rec.h"

short mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations){

	short	recommendation, trial_recommendation;
	double 	highest_score = 0.0, trial_score = 0.0;
	Deck *	mc_deck = init_deck(52,NULL,1);
	
	deck_remove_cards(mc_deck, hand->cards, 5);
	mc_deck->shuffle(mc_deck);
	
	for(trial_recommendation=0;i++;i<32){
		trial_score = score_trial_rec(trial_recommendation, *hand, poker_hands, mc_deck, iterations);
		if(trial_score > higest_score){
			highest_score = trial_score;
			recommendation = trial_recommendation;
		}
	}
	return recommendation;
}

double score_trial_rec(short trial_recommendation, Hand hand, Hand_rank * poker_hands, Deck * deck, int iterations){

	int removed_cards_count = 0;
	double score;
	int i;

	Card * first_opening;

	for(i=0;i<5;i++){
		if(trial_recommendation && 1)
			hand->remove(hand,i+1,0);
			removed_cards_count++;
			trial_recommendation = trial_recommendation>>1;
		}
	}
	
	/* If all cards remain simply return this hand's value */

	if(removed_cards_count == 0){
		return rank_hand(&hand, poker_hands)->cumulative_prob;
 
	hand->sort(hand);

	first_opening = hand.cards + (5-removed_cards);
	
	for(i=0; i<iterations; i++){
		quick_shuffle(deck, removed_cards_count);
		memcpy(first_opening, deck->cards, sizeof(Card) * removed_cards_count);
		score += rank_hand(hand, poker_hands)->cumulative_prob;	
	}

	return score / (double)iterations;
}

void	quick_shuffle(Deck * deck, int n_cards){

	int i;
	int random_index;
	Card switch_card;

	for(i=0;i<n_cards;i++){
		random_index = rand() % (deck->cards->n_items + 1);
		card_swap(deck->cards[i], deck->cards[random_index], buffer);
	}
}			
						
void print_recommendation(short recommendation, int type){

	int i;
	
	if(type == 0){
		printf("Recommended to discard cards: ");
		for(i=1;i<6;i++){
			if(recommendation && 1){
				printf("%d ",i);
			}	
			recommendation = recommendation>>1;
		}
	else
		for(i=1;i<6;i++){
			if(recommendation && 1){
				printf("^  ");
			}
			else
				printf("   ");
			}
		}
	}
}
}	
