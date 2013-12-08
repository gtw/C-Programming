#ifndef MC_REC_H
#define MC_REC_H

#include "deck.h"
#include "poker_hands.h"

int[5] 	mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations);
double 	score_trial_rec(short trial_recommendation, Hand hand, Hand_rank * poker_hands, Deck * deck, int iterations);
void	quick_shuffle(Deck * deck, int n_cards);
void	print_recommendation(short recommendation, int type);

#endif
