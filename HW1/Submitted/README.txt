Gian Thomas Wrobel
Homework 1

General Sources of Information:
	
	<ctype.h>
	
	The "C Programming Second Edition" was used as a reference throughout this assignment
	but in particular proved important in learning the functionality of the <ctype.h> header
	file which is used essentially every time I was asked to parse data from a file. (e.g.
	Question 9 and 10).

	qsort
	
	My code occasionally makes use of the "qsort" method for which I had to write custom
	"compare" functions.  The URL below was my primary source of information regarding
	the funcctionality of the qsort method.
	
	http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml

	Bitwise Operators
	
	While my use of bitwise operators in questions 7 and 8 is my own work, I did search online
	to find information on how bitwise operations are called in C.  In my opinion, most of the
	credit to these problems go to Prof. Siegel anyway for noting how one might create a long
	integer pointer to an address in memory original stored as a float in order to perform
	bitwise operations on them.  Below is a sample link of a site I used for reference.
	
	http://www.cprogramming.com/tutorial/bitwise_operators.html
	
Shortcomings of Code:
	
	Problem 6: I want to make very explicit that the permutations algorithm implemented in
		problem 6 is not my own original work, and that while I have spent a great deal
		of time using it and believe I understand it quite well, I did not write it myself.
		I was considering many more convoluted methods of developing permutations, most of
		which involved allocating a great deal of space to empty strings I would slowly populate.
		I am aware of the instructions of the problem and wish for this problem to be graded accordingly,
		but facing some time constraints and wishing to at least attempt every problem I have
		built some code that works well around this method and have taken the method from the URL below.
		
		http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
		
		If I had more time I also would implement a function which output these files into an array and then would sort
		them either by using string compare or simply by writing my own function.  At the moment I print
		all outcomes, including duplicates, and I do not sort alphabetically.
		
	Throughout the code I have attempted to explain my reasoning.  There are simple instances where
		moving blocks of code into a separate function would've been wise.  As is, however, the greatest
		single shortcoming is that noted above for problem 6.
		

