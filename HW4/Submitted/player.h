#ifndef PLAYER_H
#define PLAYER_H

#include "deck.h"
#include "hand_rank.h"

typedef struct player {

	Hand 	  *hand;
	char 	  *name;
	int	   chips;
	int	   human;
	int	   fold;
	int        all_in;
	int        current_bet;
	int	   (*bet)(struct player * player, int last_bet, int limit, int pot, int opponents, Hand_rank * poker_hands);
	int        (*destroy)(struct player * player);

} Player;

int	 user_letter(void);
int	 player_bet(Player * player, int last_bet, int limit, int pot, int opponents, Hand_rank * poker_hands);
int	 player_destroy(Player * player);
Player * init_player(char * name, int human, int chips);   

#endif
