#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hand_rank.h"
#include "deck.h"

Hand_rank * import_rank_data(void){

	int i;
	char key[20];
	char cumulative_prob[20];
	char rank[10];

	FILE *hands_file;
	Hand_rank * poker_hands = (Hand_rank*)malloc(sizeof(Hand_rank)*7462);
	
	hands_file = fopen("poker_hands.txt", "r");

	for(i=0;i<7462;i++){
		poker_hands[i].desc = calloc(26,sizeof(char));
		fscanf(hands_file, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", key, poker_hands[i].desc, cumulative_prob, rank);
		poker_hands[i].key = atol(key);
		poker_hands[i].cumulative_prob = atof(cumulative_prob);
		poker_hands[i].rank = atoi(rank);
	}

	return poker_hands;
}

int main(int argc, char* argv[]){

	int i;
	
	Hand_rank * poker_hands = import_rank_data();

	for(i=7461;i>7451;i--){
		printf("%ld %s %f %d\n", poker_hands[i].key, poker_hands[i].desc, poker_hands[i].cumulative_prob, poker_hands[i].rank);
	}

	free(poker_hands);
	return 0;
}
