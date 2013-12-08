#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hand_rank.h"
#include "mc_rec.h"

short mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations){

	short	recommendation, trial_recommendation;
	double 	highest_score = 0.0; 
	double 	trial_score;
	Deck *	mc_deck = init_deck(52,NULL,1);
	
	deck_remove_cards(mc_deck, hand->cards, 5);
	mc_deck->shuffle(mc_deck);
	
	for(trial_recommendation = 0; trial_recommendation < 32; trial_recommendation++){
		trial_score = score_trial_rec(trial_recommendation, hand, poker_hands, mc_deck, iterations);
		printf("Trial %d Score is %f\n", trial_recommendation, trial_score);
		if(trial_score > highest_score){
			highest_score = trial_score;
			recommendation = trial_recommendation;
		}
	}
	return recommendation;
}

double score_trial_rec(short trial_recommendation, Hand * hand, Hand_rank * poker_hands, Deck * deck, int iterations){

	int removed_cards_count = 0;
	double score;
	int i;
	Card * copy_cards = (Card*)malloc(sizeof(Card) * hand->size);
	Card * buffer = (Card*)malloc(sizeof(Card));
	Card * first_opening;
	
	memcpy(copy_cards, hand->cards, sizeof(Card) * hand->size);

	for(i=1;i<6;i++){
		if(trial_recommendation & 1){
			hand->remove(hand,i,0);
			removed_cards_count++;
			trial_recommendation = trial_recommendation>>1;
		}
	}
	
	/* If all cards remain simply return this hand's value */

	if(removed_cards_count == 0){
		return ((rank_hand(hand, poker_hands))->cumulative_prob);
 	}

	else{
		hand->sort(hand);

		first_opening = hand->cards + (5-removed_cards_count);
		
		for(i=0; i<iterations; i++){
			quick_shuffle(deck, removed_cards_count, buffer);
			memcpy(first_opening, deck->cards->data, sizeof(Card) * removed_cards_count);
			score = score + ((rank_hand(hand, poker_hands))->cumulative_prob);	
		}
	}

	memcpy(hand->cards, copy_cards, sizeof(Card) * hand->size);
	
	return (score / (double)iterations);
}

void	quick_shuffle(Deck * deck, int n_cards, Card * buffer){

	int i;
	Card *c = (Card*)deck->cards->data;

	for(i=0;i<n_cards;i++){
		card_swap(&(c[i]), &(c[rand() % (deck->cards->n_items +1)]), buffer);
	}
}			
						
void print_recommendation(short recommendation, int type){

	int i;
	
	printf("Recommendation Value is: %d\n", recommendation);

	if(type == 0){
		printf("Recommended to discard cards: ");
		for(i=1;i<6;i++){
			if(recommendation & 1){
				printf("%d ", i);
			}	
			recommendation = recommendation>>1;
		}
	}
	else{
		for(i=1;i<6;i++){
			if(recommendation & 1){
				printf("^  ");
			}
			else{
				printf("   ");
			}
		}
	}
	printf("\n");
}	
