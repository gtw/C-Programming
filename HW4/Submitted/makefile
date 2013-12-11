CC = gcc
CFLAGS = -c -ansi -Wall -pedantic

play_poker: poker.o deck.o hand_rank.o mc_rec.o player.o queue.o table.o
	$(CC) $(CFLAGS) -o play_poker poker.o deck.o hand_rank.o mc_rec.o player.o queue.o table.o

poker.o: deck.h mc_rec.h table.h hand_rank.h
	$(CC) $(CFLAGS) -c poker.c

deck.o: deck.h
	$(CC) $(CFLAGS) -c deck.c

hand_rank.o: hand_rank.h deck.h
	$(CC) $(CFLAGS) -c hand_rank.c

mc_rec.o: hand_rank.h mc_rec.h
	$(CC) $(CFLAGS) -c mc_rec.c

player.o: player.h hand_rank.h
	$(CC) $(CFLAGS) -c player.c -lm

queue.o: queue.h
	$(CC) $(CFLAGS) -c queue.c

table.o: table.h mc_rec.h hand_rank.h
	$(CC) $(CFLAGS) -c table.c
