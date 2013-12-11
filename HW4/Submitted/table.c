#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#include "mc_rec.h"
#include "hand_rank.h"
#define  WAIT 1

void	table_remove_players(Table * table){

	int i;
	int j;
	int orig_player_ct = table->n_players;
	int removed_count = 0;
	Player **p = table->players;

	for(i = 0; i < orig_player_ct; i++){
		
		j = i - removed_count;
	
		if(p[j]->chips <= 0){
			if(p[j]->human)
				printf("You have run out of chips!\n");
			else
				printf("%s has run out of chips!\n", p[j]->name);
		
			p[j]->destroy(p[j]);
			removed_count++; 
			(table->n_players)--;
			if(j < (orig_player_ct - 1)){
				memmove(&p[j], &p[j+1], sizeof(Player*) * (orig_player_ct - j));
			}
		}
	}
}

void	table_zero_bets(Table * table){

	int i;
	Player ** p = table->players;
	
	for(i=0; i < table->n_players; i++){

		p[i]->current_bet = 0;
	}
}

void	table_bet(Table * table){

	int current_bet;
	int last_bet = 0;
	int no_raise = 0;
	Player ** p = table->players;
	int i = 0;

	while(no_raise < table->n_players){
		
		i = i%table->n_players;	
		
		if(p[i]->fold == 0 && p[i]->all_in == 0){
			sleep(1);	
			current_bet = p[i]->bet(p[i], last_bet, table->limit, table->pot, (table->players_n_folded - 1), table->poker_hands);
			
			if(current_bet == -1){
				printf("%s folds.\n", p[i]->name);
				table->players_n_folded--;
				no_raise++;
			}
			else if(current_bet == 0){
				printf("%s checks\n",p[i]->name);
				no_raise++;
			}
			else if(current_bet == last_bet){
				printf("%s calls to $%d\n", p[i]->name, current_bet);
				no_raise++;
			}
			else{
				printf("%s raises to $%d\n", p[i]->name, current_bet);	
				no_raise = 1;
			}
			
			if(current_bet != -1){	
				table->pot += (current_bet - p[i]->current_bet);
				p[i]->chips = p[i]->chips - (current_bet - p[i]->current_bet);
			}

			if(p[i]->chips <= 0 && p[i]->fold == 0){
				p[i]->all_in = 1;
				printf("%s is all in!\n", p[i]->name);
			}
			
			if(current_bet != -1){
				last_bet = current_bet;
			}
		}	
		else{
			no_raise++;
		}
		i++;
	}
}

void	table_winner(Table * table){

	int i;
	int winner;
	double current_score;
	double top_score = 0.0;
	Player ** p = table->players;

	for(i=0; i<table->n_players; i++){
		
		if(p[i]->fold == 0){
			current_score = rank_hand(p[i]->hand, table->poker_hands)->cumulative_prob; 
			if(current_score > top_score){
				winner = i;
				top_score = current_score;
			}
		}
	}
	
	printf("%s has won the pot with %s.  $%d added to their chips.\n", p[winner]->name, rank_hand(p[winner]->hand, table->poker_hands)->desc, table->pot);
	sleep(1);
	p[winner]->chips = p[winner]->chips + table->pot;
	table->pot = 0;
}

/*	Collects the ante from all players and resets the number of "non-folded" players to the number in
	this hand */

void	table_ante(Table * table){
	
	int i;
	Player **p = table->players;

	table->players_n_folded = table->n_players;

	for(i = 0; i < table->n_players; i++){
		if(p[i]->chips < table->limit){
			table->pot += p[i]->chips;
			printf("%s antes $%d\n", p[i]->name, p[i]->chips);
			p[i]->chips = 0;
		}
		else{
			table->pot += table->limit;
			p[i]->chips = p[i]->chips - table->limit;
			printf("%s antes $%d\n", p[i]->name, table->limit);
		}
		sleep(WAIT);
	}
	printf("\n");
}
				
void	table_return_cards(Table * table){

	int i;

	for(i=0; i < table->n_players; i++){
		remove_rec_cards(31, table->players[i]->hand, table->deck);
	}

}

void	table_new_cards(Table * table){

	int      i;
	int      j;
	int      removed_count;
	int      unacceptable_input = 1;
	char	 player_input; 
	short    recommendation;
	short	 current_binary = 1;
	short	 user_gen_rec = 0;
	Player **p = table->players;
	
	for(i = 0; i < table->n_players; i++){
		sleep(WAIT);
		if(p[i]->fold == 0){
			recommendation = mc_recommend(p[i]->hand, table->poker_hands, table->iterations, poker_hand_rec);
			if(p[i]->human == 0){
				removed_count = remove_rec_cards(recommendation, p[i]->hand, table->deck);
				printf("%s has received %d new cards.\n", p[i]->name, removed_count);
				for(j = 0; j < removed_count; j++){
					p[i]->hand->add(p[i]->hand, table->deck->pick_card(table->deck));
				}
			}
			else{
				printf("Recommended cards to discard\n");
				p[i]->hand->print(p[i]->hand);
				print_recommendation(recommendation,1);
				while(unacceptable_input){
					printf("Do you wish to accept this recommendation? (y/n)\n");
					player_input = user_letter();
					if(player_input == 'y' || player_input == 'n'){
						unacceptable_input = 0;
					}
				}
	
				if(player_input == 'y'){
					removed_count = remove_rec_cards(recommendation, p[i]->hand, table->deck);
					printf("You have received %d new cards.\n", removed_count);
					for(j = 0; j < removed_count; j++){
						p[i]->hand->add(p[i]->hand, table->deck->pick_card(table->deck));
					}
				}
				else{
					current_binary = 1;
	
					for(j = 0; j < p[i]->hand->size; j++){
						unacceptable_input = 1;
						while(unacceptable_input){
							printf("Remove ");
							val_print(p[i]->hand->cards[j].val);
							suit_print(p[i]->hand->cards[j].suit);
							printf("? (y/n)\n");
							player_input = user_letter();
							if(player_input == 'y' || player_input == 'n')
								unacceptable_input = 0;
						}
						if(player_input == 'y')
							user_gen_rec = user_gen_rec | current_binary;	
						current_binary = current_binary<<1;
					}
					
					removed_count = remove_rec_cards(user_gen_rec, p[i]->hand, table->deck);
					printf("You have received %d new cards.\n", removed_count);
					for(j = 0; j < removed_count; j++){
						p[i]->hand->add(p[i]->hand, table->deck->pick_card(table->deck));
					}				
				}			
			}
		}
	}
}	
/*	Used to change who goes first after each hand.  The person at the front of the
	array of pointers storing players is moved to the back and everyone else is moved forward */

void	table_shift(Table * table){
	
	Player * buffer;
	Player ** p = table->players;

	buffer = p[0];
	memmove(&(p[0]), &(p[1]), sizeof(Player*) * ((table->n_players) - 1));
	p[table->n_players-1] = buffer;
}

/*	Players who are "all_in" or "folded" are reset to not be following a hand */

void	table_unfold(Table * table){

	int i;

	for(i=0; i < table->n_players; i++){
		table->players[i]->fold = 0;
		table->players[i]->all_in = 0;
	}
}

/*	For each player it deals to them from the deck a number of cards equal to how
	many are currently missing from their hand */

void    table_deal(Table * table){

	int i;

	for(i=0; i < table->n_players; i++){
		table->players[i]->hand->sort(table->players[i]->hand);
		while(table->players[i]->hand->cards_in_hand < table->players[i]->hand->size){
			table->players[i]->hand->add(table->players[i]->hand, table->deck->pick_card(table->deck));
		}
	}
}
				
/* 	Two ways of printing the current state of the table */

void	table_print(Table * table, int type){

	int i;
	Hand_rank curr_rank;
	Player ** p = table->players;

	if(type == 0){
		for(i=0; i < table->n_players; i++){
			printf("%s: $%d  ", p[i]->name, p[i]->chips);
		}
		printf("\n");
	}
	
	else if(type == 1){
		for(i=0; i < table->n_players; i++){
			if(p[i]->fold == 0){
				curr_rank = *rank_hand(p[i]->hand, table->poker_hands);
				printf("%s: %s\n",p[i]->name, curr_rank.desc);
				p[i]->hand->print(p[i]->hand);
				printf("\n");
			}	
		}
	}
}
/*	Simple function to propogate player names.  Called by table_init */

char  * comp_player_names(int i){

	char * name1 = "Zaphod Beeblebrox";
	char * name2 = "The One True Lord";
	char * name3 = "Cher";

	if(i == 1)
		return name1;
	else if (i == 2)
		return name2;
	else
		return name3;
}

/*	Most of the logic built into the beginning of this function is redundant since my poker.c
	file begins by checking these conditions as well before initializing the game */

Table * init_table(char * human, int n_players, int limit, int starting_amount, int iterations){
	
	int i;

	Table * table;

	if(n_players < 2 || n_players > 4){
		printf("Must select between 2 and 4 players\n");
		return NULL;
	}

	if(starting_amount < limit){
		printf("Limit must be less than starting amount\n");
		return NULL;
	}

	if(starting_amount % limit != 0){
		printf("Starting amount must be a multiple of the limit\n");
		return NULL;
	}

	table = (Table*)malloc(sizeof(Table));
	
	if(table==NULL){
		printf("Error, no space for table");
		return NULL;
	}

	table->players = malloc(sizeof(Player*) * n_players);
	if(table->players==NULL){
		printf("Error, no space for table");
		return NULL;
	}
	
	table->players[0] = init_player(human, 1, starting_amount);
	for(i=1; i < n_players; i++){
		table->players[i] = init_player(comp_player_names(i), 0, starting_amount);
	}

	table->iterations       = iterations;
	table->poker_hands      = import_rank_data();
	table->pot              = 0;
	table->starting_amount  = starting_amount;
	table->limit            = limit;
	table->n_players        = n_players;
	table->players_n_folded = n_players;
	table->deck             = init_deck(52, NULL, 1);

	return table;
}
