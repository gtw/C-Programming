CC = gcc
CFLAGS = -c -ansi -Wall -pedantic

play_poker: poker.o deck.o hand_rank.o mc_rec.o player.o queue.o table.o
	$(CC) -o play_poker poker.o deck.o hand_rank.o mc_rec.o player.o queue.o table.o -lm

poker.o: poker.c deck.c deck.h mc_rec.c mc_rec.h table.c table.h hand_rank.c hand_rank.h
	$(CC) $(CFLAGS) poker.c

deck.o: deck.c deck.h
	$(CC) $(CFLAGS) deck.c

hand_rank.o: hand_rank.c hand_rank.h deck.c deck.h
	$(CC) $(CFLAGS) hand_rank.c

mc_rec.o: hand_rank.c hand_rank.h mc_rec.c mc_rec.h
	$(CC) $(CFLAGS) mc_rec.c

player.o: player.c player.h hand_rank.c hand_rank.h
	$(CC) $(CFLAGS) player.c -lm

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) queue.c

table.o: table.c table.h mc_rec.c mc_rec.h hand_rank.c hand_rank.h
	$(CC) $(CFLAGS) table.c

clean:
	rm *.o
