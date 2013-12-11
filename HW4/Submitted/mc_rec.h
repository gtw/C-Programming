#ifndef MC_REC_H
#define MC_REC_H

#include "deck.h"
#include "hand_rank.h"

short 	mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations, double (*scoring_function)(short trial_num, Hand * hand, void * scoring_data, Deck * deck, int iterations));
double 	poker_hand_rec(short trial_recommendation, Hand * hand, void * scoring_data, Deck * deck, int iterations);
double  random_rec(short trial_recommendation, Hand * hand, void * scoring_data, Deck * deck, int iterations);
void	quick_shuffle(Deck * deck, int n_cards, Card * buffer);
void	print_recommendation(short recommendation, int type);
int     remove_rec_cards(short recommendation, Hand * hand, Deck * deck);

#endif
