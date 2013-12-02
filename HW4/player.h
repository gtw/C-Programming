#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {

	Hand *     hand;
	double     chips;
	int	   (*change_chips)(struct player * player, double amount);
} Player;

#endif
