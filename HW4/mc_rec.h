#ifndef MC_REC_H
#define MC_REC_H

#include "deck.h"
#include "poker_hands.h"

int[5] mc_recommend(Hand * hand, Hand_rank * poker_hands, int iterations);

#endif
