# dictionary
<h1>Project Description: </h1>
This project uses a ‘dictionary’ file to find frequency of words and correct spelling mistakes of words from a passage or extract. The dictionary is implemented using an Adelson-Velsky and Landis Tree also commonly known as an AVL Tree.
A text file called “dictionary” containing a list of words is given. At the beginning of the program the dictionary text file is read, and an AVL tree is created with those words. The dictionary tree is then used alongside another text file to check for spelling mistakes in the file, correcting spellings and finding frequency of words in the text files.

<h2>Data: </h2>

-	Dictionary: A text file consists of a distinct set of words separated by spaces.
-	Test file: Test files are random passages or extracts. They include punctuation, new lines and other characters. There are 3 types of input files:
-	Clean file: One-page text file with around 300 words.
-	Mutated file: One-page text file with a character in a word substituted with another random character e.g. disciple and d;sciple

<h2>Methods:</h2> 
<h3> •	insert() 	</h3>		// used to insert a new node in AVL tree
Time complexity: O(log N)

-	leftRotate() 		// used for left rotation of AVL tree
-	rightRotate() 		// used for right rotation of AVL tree
-	getBalance() 		// returns the depth of left side minus right side to check balance of tree

<h3> •	deleteNode()	</h3> 		// deletes a node form the AVL tree
Time complexity: O(log N)

<h3> •	InOrder()	</h3>		// used for inorder traversal of tree
Time complexity: O(N)

<h3> •	countNodes() 	</h3>		// counts the number of nodes in the AVL tree

<h3> •	Search()	</h3> 		// used to search a node in the tree against a key word
Time complexity: O(log N)

<h3> •	countFrequency()	</h3> 	// counts the frequency of the words in the dictionary file in test file

<h3> •	checkMutated()		</h3>// checks spelling mistake in a word and returns the corrected word

<h3> •	removePunctuation() 	</h3>	// removes special characters from words when reading a file

<h3> •	convertToLowerCase()	</h3> 	// converts all incoming text to lowercase

<h3> •	bstComparison()	</h3>	//consists of traversals in two trees

- 	traverse()		//acts as outer for loop and traverses inputFile BST
- 	compare()		//acts as inner for loop and traverses through dictionary BST
