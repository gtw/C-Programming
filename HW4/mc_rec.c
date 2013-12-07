#include <stdlib.h>
#include "mc_rec.h"

int[5] mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations){

	int 	c1, c2, c3, c4, c5;
	int 	recommendation[5], trial_recommendation[5];
	double 	highest_score = 0.0, trial_score = 0.0;
	Deck *	mc_deck = init_deck(52,NULL,1);
	
	deck_remove_cards(mc_deck, hand->cards, 5);
	mc_deck->shuffle(mc_deck);
	
	for(c1=0;c1<2,c1++){
		trial_recommendation[0] = c1;
		for(c2=0;c2<2;c2++){
			trial_recommendation[1] = c2;
			for(c3=0;c3<2;c3++){
				trial_recommendation[2] = c3;
				for(c4=0;c4<2;c4++){
					trial_recommendation[3] = c4;
					for(c5=0;c5<2;c5++){
						trial_recommendation[4] = c5;
						trial_score = score_trial_rec(trial_recommendation, hand, mc_deck, iterations);
						if(trial_score > higest_score){
							highest_score = trial_score;
							memcpy(recommendation, trial_recommendation, sizeof(int)*5);
						}
					}
				}
			}
		}
	}

	return recommendation;
}

double score_trial_rec(int trial_recommendation[5], Hand * hand, Deck * deck, int iterations){

	int removed_cards_count = 0;
	int i;
	
	for(i=0;i<5;i++){
		if(trial_recommendation[i] = 1){
			hand->remove(hand,i+1,0);
			removed_cards_count++;
		}
	}

	hand->sort(hand);
	
	for(i=0; i<iterations; i++){
		
	

