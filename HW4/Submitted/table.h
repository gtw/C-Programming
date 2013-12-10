#ifndef TABLE_H
#define TABLE_H

#include "deck.h"
#include "player.h"
#include "hand_rank.h"
#include <string.h>
#include <stdio.h>

typedef struct table {

	Player 	  **players;
	Deck	   *deck;
	Hand_rank  *poker_hands;
	int	    iterations;
	int	    pot;
	int	    limit;
	int	    starting_amount;
	int	    n_players;
	int	    players_n_folded;

} Table;

void	table_zero_bets(Table * table);
void	table_bet(Table * table);
void	table_unfold(Table * table);
void	table_shift(Table * table);
void	table_winner(Table * table);
void	table_ante(Table * table);
void	table_remove_players(Table * table);
void	table_new_cards(Table * table);
void	table_print(Table * table, int type);
void    table_deal(Table * table);
void	table_return_cards(Table * table);
char  * comp_player_names(int i);
Table * init_table(char * human, int n_players, int limit, int starting_amount, int iterations);	

#endif
