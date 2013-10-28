Gian Thomas Wrobel
HW 2
CSPP 51040
October 28, 2013

Sources Referenced in the Completion of this Assignment:

	Frequent references have been made to Kernighan and Ritchie
		in the determination of the proper use of arrays, pointers,
		strings, and their related syntax. While typically this book
		was used for general reference, in answering question 10 I
		did make particular use of section 5.5, which discussed the
		implementation of strcpy and strcmp.  Since the problem
		called for the creation of a clone of strncpy and strncmp,
		I felt it appropriate to use these sections as a guide for how
		to make these slightly more complicated functions.
		
	In answering question 4 I made use of resources made available by
		MIT's CSAIL lab, which has published the following pseudocode
		outlining a typical implementation of a heap.  Conversation with
		the TAs has led me to believe it is appropriate to implement methods
		found in this manner as long as the implementation is our own.
		
		http://courses.csail.mit.edu/6.006/fall10/handouts/recitation10-8.pdf
		
	In researching the functionality of various string functions which
		were implemented in question 10 of this homework assignment I made
		use of the following website (an example page is linked).
		While I didn't take any code from this website specifically, it
		was useful in exploring the functionality of various string functions.
		
		http://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm
		
Code Shortcomings:

	Problem 5: My sort is case-sensitive.  I don't think this is a major issue,
		but I'm mentioning it here for now.  My sort really is just a wrapper for
		strcmp.  The real work was done reading in the file dynamically.
	
		I have also decided to ignore multiple newlines in a row so I never read
		in a blank line.  This was just a choice I made which was not mentioned
		in the problem.
