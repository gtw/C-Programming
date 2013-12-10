#ifndef MC_REC_H
#define MC_REC_H

#include "deck.h"
#include "hand_rank.h"

short 	mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations);
double 	score_trial_rec(short trial_recommendation, Hand * hand, Hand_rank * poker_hands, Deck * deck, int iterations);
void	quick_shuffle(Deck * deck, int n_cards, Card * buffer);
void	print_recommendation(short recommendation, int type);
int     remove_rec_cards(short recommendation, Hand * hand, Deck * deck);

#endif
