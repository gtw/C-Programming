#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "player.h"
#include "deck.h"
#include "hand_rank.h"
#define  WAIT 1

/*	Used to get a single character from  the command line and clean out stdin afterwards*/

int	user_letter(void){

	int c;
	int first;
	
	first = c = getchar();
	while(c != '\n' && c != EOF)
		c = getchar();
	
	return first;
}

/*	Implements player betting logic.  You cannot raise more than 4 times. If no one raises for an
	entire circle of the table the round of betting is over */

int	player_bet(Player * player, int last_bet, int limit, int pot, int opponents, Hand_rank * poker_hands){

	Hand_rank *player_hand_rank;
	int	   raise_amount;
	int	   call_amount;
	char       human_bet;
	char       all_in_choice;
	int        unacceptable_input = 1;

	player_hand_rank = rank_hand(player->hand, poker_hands);
	raise_amount = last_bet + limit - player->current_bet;
	call_amount = last_bet - player->current_bet;

	if(player->human){
		printf("\nIt's Your Turn: %s\n\n", player->name);
		sleep(WAIT);
		player->hand->print(player->hand);  
		printf("Hand: %s\nStrength: %3.2f%%\n\n", player_hand_rank->desc, 100 * player_hand_rank->cumulative_prob);
		printf("Pot: $%d     Your Chips: $%d     To Call: $%d     To Raise: $%d\n\n", pot, player->chips, last_bet, last_bet + limit);
		sleep(WAIT);
		printf("To call/check type 'c'.  To raise type 'r'. To fold type 'f'\n");
		while(unacceptable_input){
			human_bet = user_letter();
			if(human_bet != 'c' && human_bet != 'r' && human_bet != 'f'){
				printf("Please choose 'c', 'r', or 'f'\n");
			}
			else if(human_bet == 'r' && (last_bet + limit > limit * 4)){
				printf("The maximum bet for a round of betting is $%d\n", limit * 4);
				printf("Please choose 'c' or 'f'\n");
			}
			else if(human_bet == 'c' && call_amount > player->chips){
				printf("You don't have enough chips to call, do you wish to go all in? (y)\n");
				printf("If you fold with no chips in hand, you're out of the game!\n");
				all_in_choice = user_letter();
				if(all_in_choice == 'y'){
					unacceptable_input = 0;
					return last_bet + player->chips;
				}
				else{
					printf("Please choose 'c', 'r', or 'f'\n");
				}
			}
			else if(human_bet == 'r' && raise_amount > player->chips){
				printf("You don't have enough chips to raise, do you want to go all in? (y)\n");
				printf("Note you may be able to call but if you fold with no chips you are out\n");
				all_in_choice = user_letter();
				if(all_in_choice == 'y'){
					unacceptable_input = 0;
					return last_bet + player->chips;
				}
				else{
					printf("Please choose 'c', 'r', or 'f'\n");
				}
			}
			else{
				unacceptable_input = 0;
			}
		}
		if(human_bet == 'f'){
			player->fold = 1;
			return -1;
		}
		else if(human_bet == 'c'){
			return last_bet;
		}
		else{
			return last_bet + limit;
		}
		printf("\n");
	}
	else{
		if((pow(player_hand_rank->cumulative_prob, (double)opponents) * (pot + raise_amount) > raise_amount) && player->chips >= raise_amount && (last_bet + limit <= 4 * limit)){
			return last_bet+limit;
		}
		else if((pow(player_hand_rank->cumulative_prob, (double)opponents) * (pot + call_amount) > call_amount) && player->chips >= call_amount ){
			return last_bet;
		}
		else{
			player->fold = 1;
			return -1;
		}
	}	
}

int	player_destroy(Player * player){

	player->hand->destroy(player->hand);
	free(player);
	return 0;
}
	
Player * init_player(char * name, int human, int chips){

	Player * player = (Player*)malloc(sizeof(Player));
	
	if(player == NULL){
		printf("No space for player.\n");
		return NULL;
	}

	player->name        = name;
	player->hand        = hand_init(5);
	player->chips       = chips;
	player->human       = human;
	player->fold        = 0;
	player->all_in      = 0;
	player->current_bet = 0;
	player->bet         = player_bet;
	player->destroy     = player_destroy; 

	return player;
}
