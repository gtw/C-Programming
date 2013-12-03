#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "hand_rank.h"

int main(int argc, char * argv[]){

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
		poker_hands[i].key = atol
