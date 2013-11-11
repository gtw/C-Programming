Gian Thomas Wrobel
HW3
November 11, 2013

Resources Used:

	In solving p2 I relied on discussion and other students during office hours.
		The implementation, however, is entirely my own.
	
	Otherwise for this assignment I only rarely consulted the textbook for
		syntax questions.
		
Shortcomings:

	In p5 I initialize an ArrayList of size 0 to have capacity 1 but size 0. This is
	done to prevent the ambiguous case of mallocing zero bytes of memory.  From the user's
	standpoint they will interact with the ArrayList no differently than otherwise, and the
	way our wrapper functions like "get" and "set" are written they will not easily
	gain access to that address in memory.
	
	Additionally in p5 I am unsure as to whether my code will append the 10,000,000 ints
	in the time required.  On my machine it is taking a few seconds longer than 3 (maybe 6-7),
	but I am running Ubuntu from a virtual box so it is almost certainly slower than
	the CS machines.  After consulting my code I am fairly certain there is no faster way to use
	an array as the underlying structure while doubling the capacity of the array when all
	allocated space is filled.
	
