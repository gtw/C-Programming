To Play:
	make clean
	make
	./play_poker

Extra Credit:

	I have attempted the extra credit and believe I have done so successfully.  While the absolute
		ranking of each hand is stored in my "hand_rank" objects, I never use it.  I always use the
		CDF function to rank hands, compare them, and make bets.  See the "hand_rank.c" module description
		below for more information about where I got my data and how I ranked them.  Also, in the email
		I sent with this project you can find the Excel workbook used to create this CDF.
		
Shortcomings:
	
	I could always speed up the MC Recommender by creating even more efficient data structures for
		my cards and using more bitwise operations.  I just didn't have the time and as is things move
		relatively quickly.  I've hard coded in 100,000 trials for each possible combination of cards
		which is plenty to get an accurate recommendation and it currently only takes a couple seconds
		for each player.
		
	Betting structure and logic is somewhat simplistic though not terrible.  I certainly lose to the
		computer players frequently enough.  I also have limited chip amounts to ints rather than
		doubles so if someone splits an odd numbered pot some integer division will happen and a dollar
		will be "lost to the house".  I'm ok with that though, because the house worked a really long
		time coding this thing up and probably deserves the dollar.  Also because my scoring considers
		kickers the actual chances of splitting a pot are extremely low.
		
	Names must be less than 50 characters.  Probably need to put something in to deal with the potential
		for overflow.
		

Included Modules:

	poker.c: The main function can be found within this module.  The program begins by prompting
		the user to enter their name and select the number of players they wish to be in the game.
		The human player has the choice of playing anywhere from 1 to 3 computer players for up to
		4 total players.  For simplicity of design I have coded the betting structure as a "limit"
		game, in which antes, bets, and raises all must be a multiple of some given "limit".  I also
		require the amount each player starts with to be a multiple of this limit, so that there are
		not odd amounts left over as a player is exiting the game.
		
		Once initialized the game simply plays hands until a single player is remaining and declares
		them the winner.  Hands use the following structure:
		
			- Print standings
			- Collect antes
			- Begin first round of betting
			- Exchange cards with deck
			- Begin second round of betting
			- Reveal hands
			- Distribute winnings
			- Remove players who are out of chips
			- Reset table and player values (folded, pot value, etc)
			
		At the end of each hand the order of play is shifted, so that the player who bet and received
		cards first last time now does so last.
		
		While this module "runs" the game, it essentially is just used to call functions held in the
		table.c module.
		
	table.c: contains the deck, players, information about the game like the limit, starting value,
		a ranking of all possible hands called "poker hands", as well as information about how many
		players have not yet folded.  There is also a variable for how many iterations the Monte-Carlo
		simulator should use when called, though this value is hard coded in the poker.c module to 100,000
		for regular gameplay.  Almost all functions relating to gameplay are contained in this module.
		
			- table_zero_bets: returns player bets to zero after each round of betting
			- table_bet: initiates a round of betting.  Players can call/check, raise, or fold
					only players who haven't folded are asked for a new bet.  Bets cannot exceed 4 times
					the table limit.  The betting logic itself, however, is in the player module.
			- table_unfold: resets all players to unfolded at the start of a hand
			- table_shift: handles shifting which player will lead off each hand of betting
			- table_winner: examines players hands at the end of round to assign a winner and distribute pot
			- table_ante: collects antes from players.  Antes are equal to the limit.
			- table_remove_players: removes players with no chips from the table at the end of the round
			- table_new_cards: only function in live play that calls the Monte-carlo advisor.  Gives computer
					players new cards and prompts user to select which cards to discard.
			- table_print: handles instances when information about all live players should be printed
			- table_deal: deals cards to players
			- table_return_cards: returns all cards back to the deck
			- comp_player_names: holds computer player names, to be called from the init_table function
			
	player.c: contains the player struct.  Human and computers are both player structs with an indicator
		for whether they are human.  Players have a hand, name, and chip count, as well as indicators for
		if they have folded or are all_in, and an int holding their current bet.  Only two functions are
		included, namely the "bet" function, which the table_bet function will call, and the "destroy" function
		which the table_remove_players function will call if they player's chip count goes to zero.
		
		One useful function in this module is the "user_letter" function which is used to pull in user input
		throughout the game and which removes new_lines and other stray characters to avoid leaving them in stdin.
		
		Computer betting logic is contained here and is very simple.  Computers calculate the odds that all
		other players who haven't folded have a lower hand than them by assuming independence (which is wrong but
		doing so made writing the code considerably simpler).  If their odds of winning are greater than the amount
		they must use to raise or call divided by the current pot, they will bet.  Otherwise they fold.
		
	deck.c: contains the hand, deck, and card structures.  Decks are implemented as queues and so have a number
		of functions which essentially are just wrappers for the functions found in the "queue.c" module.  The
		hand, meanwhile is just an array of cards.  Cards themselves are structures containing two enums, one for
		suit and one for hand.  Error values are included for suits and values to indicate "blank cards" or blank
		spaces in hands, decks, etc.  This module includes detailed comments regarding individual functions.
		
	queue.c: contains the queue structure on which the deck is built.  Note that my queues are of fixed size
		since I knew that in all likelihood it would only be used to hold 52 card decks.  Enqueue and dequeue
		still work, however, by keeping track of where the start of the queue is and then allowing data to be
		placed "in front" of this starting point so that the queue in effect wraps around the space dedicated
		to it.  It is possible to overflow the queue, but this didn't seem to be a problem for this application.
		I also make use of the fact that the queue is an array to "realign" the queue on occasions where I wish
		to treat it as an array and not deal with the fact that it may be wrapping around.
		
		Note my queues are written to old data of arbitrary size and have not been written to just hold cards.
		
	hand_rank.c: holds the functions associated with importing my hand rank data.  When I rank hands, I generate
		a key for each hand and then compare them to the list of "hand_rank" objects that this module imports.
		Each hand rank object contains a key of its own for comparison, as well as text describing the hand and
		data about its relative ranking and place within the CDF of this function.  I generated this data from
		a table I downloaded from this site.  
		
		http://www.suffecool.net/poker/7462.html
		
		Admittedly this was a big help, though I still needed to do some work on it.  For each possible combination
		of cards this table provides its relative ranking out of 7462 equivalence classes.  It also includes
		how often this class occurs, and text describing the hand itself.  I imported this table into Excel, and
		used the count of each hand to generate the CDF for poker hands.  A hand's value in this CDF is the sum of
		its own frequency and the frequency of every hand below it, divided by the total number of hands.  At
		this point the only remaining challenge was how I would reference this table in play.  One option was to
		sort the hands provided in the table and sort the hands in the game, but this would prove time consuming.
		
		Instead, for each face value in the standard 13 I assigned a different prime number.  By multiplying the
		values making up each hand I created unique key values which, through the incredible magic of prime factorization
		ensure I created a key value which could not be produced by any other combination of cards.  The only 
		additional challenge was to create a check for flushes in which case I multiply the key by negative one.
		The reason is in poker we differentiate between the same combination of face values if they are or are not
		of the same suit.  After I generated unique keys I created a text file which contained only these keys,
		the relative ranking, the CDF percentage, and the hand description, and imported them into my program.
		
		When I rank a hand, I use the same prime value assignment I did when creating the table to create a unique
		key.  I then use binary search to search the array of hand_rank objects created when I imported the table.
		This leads to relatively fast hand ranking, which is important for running the Monte-Carlo advisor quickly.
		If I were to improve this feature I might find a way to get around the prime assignment function and rather
		store those values along with a card.  Also in the interest of full disclosure the idea to use primes also
		came from the same site above, though he implemented some ideas with bitshifting etc that I didn't feel
		like getting into and I did not use any of his code to write my own.
		
	mc_rec.c: holds the Monte Carlo recommender.  Basically for each hand I go through all 32 combinations of cards
		one could keep and then seed the hand with the requisite number of cards from a newly generated deck
		containing the 47 cards not in the original hand. I then score this hand and add that score to a total score.
		By repeating this process thousands of times and then dividing by the number of times I scored the hand
		I can generate an average score for that choice.  If a choice has a higher average score than all previous
		recommendations, it becomes the new "best" recommendation.  Once all recommendations have been scored, the
		best recommendation is returned.
		
		Recommendations are stored as short ints with each binary digit representing whether that card in the hand should
		be kept or removed.  In particular 7, or 00111 would mean "remove the first, second, and third cards from the
		hand".  Don't get confused, however, as first second and third visually speaking starts at the left.  This
		potential source of confusion is obscured from the user however.  I also have included a function for removing
		multiple cards using a "recommendation", since we wouldn't want to sort in between removing multiple cards and
		hence mistakenly remove a different card.
		
		I have written my mc_recommender to take any function it wishes for making a recommendation for how to use a 5
		card hand, though the "poker_hand_rec" is the one used in play.  For your entertainment I have also included
		a "random_rec" function which demonstrates the flexibility of the module.  It still runs the same number of
		iterations as the "poker_hand_rec", but the scores generated for each possible recommendation are entirely
		random.  If you felt like playing some really stupid computer players, this is the recommendation function for you.
		
		
		
	
		
	
		
		

		
		


