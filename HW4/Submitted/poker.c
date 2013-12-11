#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include"deck.h"
#include"mc_rec.h"
#include"table.h"
#include"hand_rank.h"
#define WAIT 0

int main(int c, char * argv[]){

	char  *player_name = (char*)malloc(sizeof(char) * 50);
	int    n_players;
	int    starting_amount;
	int    limit;
	int    check = 1;
	Table *table;
	
	srand(time(NULL));

	printf("Welcome to Poker! What's your name?\n");
	
	while(check){
		scanf("%[^\n]s", player_name);
		if(strlen(player_name)>0){
			check = 0;
		}
		else
			printf("Player name must be more than 0 characters.\n");
	}

	check = 1;

	user_letter();	

	printf("Choose between 2 and 4 players (including yourself).\n");

	while(check){
		n_players = user_letter();
		if(n_players != '2' && n_players != '3' && n_players != '4'){
			printf("Must select between 2 and 4 players\n");
		}
		else
			check = 0;
	} 
	
	if(n_players == '2')
		n_players = 2;
	if(n_players == '3')
		n_players = 3;
	if(n_players == '4')
		n_players = 4;
	
	check = 1;	

	printf("\n");
	printf("Please choose the amount each player will begin with and the limit for each bet.\n");
	printf("Note: Limits must be less than starting amounts and starting amounts should be a\n");
	printf("\tmultiple of the limit.\n\n");

	while(check){
		printf("Starting Amount: (recommended value 100)\n");
		scanf("%d", &starting_amount);
		printf("Limit: (recommended value 5)\n");
		scanf("%d", &limit);
		
		if(starting_amount < limit){
			printf("Limit is greater than starting amount.\n\n");
		}
		else if(starting_amount % limit != 0){
			printf("Starting amount should be a multiple of limit.\n\n");
		}
		else{
			check = 0;
		}
	}

	printf("Thanks %s!  Initializing your game now!\n\n\n\n\n\n\n\n\n\n", player_name);

	table = init_table(player_name, n_players, limit, starting_amount, 100000);

	while(table->n_players > 1){
		
		table->deck->shuffle(table->deck);
		printf("Press Enter to Begin Next Hand");
		user_letter();	
		printf("\n**********************************************************************************\n");
		printf("\nBeginning New Hand\n\n");
		printf("Current Standings:\n\n");	
		table_print(table, 0);
		printf("\n**********************************************************************************\n");
		printf("\n");
		sleep(WAIT);	
	
		table_unfold(table);
		
		table_deal(table);
		
		table_ante(table);

		sleep(WAIT);
		
		printf("Beginning First Round of Betting\n");
		printf("\n**********************************************************************************\n");
		table_bet(table);

		if(table->players_n_folded > 1){
			
			printf("\n**********************************************************************************\n");
			printf("\nExchanging Cards...\n\n");
			table_new_cards(table);
			
			table_zero_bets(table);
			
			printf("\n**********************************************************************************\n");
			printf("\nBeginning Second Round of Betting\n\n");
			table_bet(table);
		}

		printf("\n**********************************************************************************\n");
		printf("\nAll rounds of betting are complete.  Revealing final hands\n\n");
	
		sleep(2);

		table_print(table, 1);

		table_winner(table);
		
		printf("\n**********************************************************************************\n");
	
		table_return_cards(table);
		
		table_shift(table);

		table_remove_players(table);

	}		

	printf("%s has won the game!\n\n", table->players[0]->name);
	return 0;
} 
