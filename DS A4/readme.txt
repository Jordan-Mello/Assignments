Jordan Mello
jmello@uoguelph.ca
22/11/18
Assignment 4 - Data Structures
Implements an AVL tree

Usage - 

"make all" to compile all. Takes command line argument for file name. For instance, running the file given to us would be
===============================
$ make all
$ ./avltree A4_data_f18.txt
===============================

Important notes - 

From original file given, there are 1,483 unique nodes, with a total count of 174,200. My AVL tree created has a height of 13. 
All functions work correctly, for all intents and purposes.

Known issues -
	• Trying to directly (intentionally) break the program
		- input overflow for the buffer of key (Keys can be 199 (200 - null character) long. Hopefully they aren't longer than that.