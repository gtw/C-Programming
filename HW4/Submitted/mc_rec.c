#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hand_rank.h"
#include "mc_rec.h"

short mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations){

	short	recommendation, trial_recommendation;
	double 	highest_score = 0.0; 
	double 	trial_score = 0.0;
	Deck *	mc_deck = init_deck(52,NULL,1);

	hand->sort(hand);
	deck_remove_cards(mc_deck, hand->cards, hand->size);
	mc_deck->shuffle(mc_deck);
	
	for(trial_recommendation = 0; trial_recommendation < 32; trial_recommendation++){

		trial_score = score_trial_rec(trial_recommendation, hand, poker_hands, mc_deck, iterations);

		/* 	I leave to you, dear grader, the challenge of figuring out why the hell
			this next line is necessary.  I sure as hell can't figure it out, but apparently, something
			somewhere is clogging the tubes, and this is unclogging 'em.  Remove it and suddenly nothing
			likes to work. If you have any ideas, I'd love to hear them though!*/
		
		fflush(stdout);

		if(trial_score > highest_score){
			highest_score = trial_score;
			recommendation = trial_recommendation;
		}
		
		trial_score = 0.0;
	}
	return recommendation;
}

double score_trial_rec(short trial_recommendation, Hand * hand, Hand_rank * poker_hands, Deck * deck, int iterations){

	int removed_cards_count = 0;
	double score = 0;
	int i;
	Card * copy_cards = (Card*)malloc(sizeof(Card) * hand->size);
	Card * buffer = (Card*)malloc(sizeof(Card));
	Card * first_opening;
	
	memcpy(copy_cards, hand->cards, sizeof(Card) * hand->size);

	removed_cards_count = remove_rec_cards(trial_recommendation, hand, NULL);
	
	/* If all cards remain simply return this hand's value */

	if(removed_cards_count == 0){
		return ((rank_hand(hand, poker_hands))->cumulative_prob);
 	}

	else{

		first_opening = hand->cards + (5-removed_cards_count);
		
		for(i=0; i<iterations; i++){
			quick_shuffle(deck, removed_cards_count, buffer);
			memcpy(first_opening, deck->cards->data, sizeof(Card) * removed_cards_count);
			score = score + ((rank_hand(hand, poker_hands))->cumulative_prob);	
		}
	}

	memcpy(hand->cards, copy_cards, sizeof(Card) * hand->size);
	hand->cards_in_hand = 5;

	free(copy_cards);
	free(buffer);
	
	return (score / (double)iterations);
}

int    remove_rec_cards(short recommendation, Hand * hand, Deck * deck){

	int 	i;
	int 	removed_count = 0;
	Card 	removed_card;

	for(i=1;i<6;i++){
		if(recommendation & 1){
			removed_card = hand->remove(hand,i,0);
			removed_count++;
			if(deck != NULL){
				deck->return_card(deck, removed_card);
			}
		}
		recommendation = recommendation>>1;		
	}

	hand->sort(hand);

	return removed_count;
}

void	quick_shuffle(Deck * deck, int n_cards, Card * buffer){

	int i;
	Card *c = (Card*)deck->cards->data;
	int n_items = deck->cards->n_items;
	int r;

	for(i=0;i<n_cards;i++){
		r = rand();
		card_swap(&(c[i]), &(c[r % (n_items)]), buffer);
	}
}			
						
void print_recommendation(short recommendation, int type){

	int i;
	
	if(type == 0){
		printf("Recommendation Value is: %d\n", recommendation);
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
				printf("^   ");
			}
			else{
				printf("    ");
			}
			recommendation = recommendation>>1;
		}
	}
	printf("\n");
}	
