#include "word.h"

class Sentence{
	public:
		Sentence();
		Sentence(string p);
		Sentence(const Sentence &sent1); // copy constructor
		void addWord(string data); // add a word to the end of the list
		void addToFront(string data); // add a word to the beginning of the list
		void show();
		string getSentence(); // return the sentence as a string
		Sentence getActualSentence(); // returns the sentence object
		Word first(); // get first word in sentence
		Sentence rest(); // get sentence minus first word
		char getPunct() const; // get the sentence's punctuation
		~Sentence();
		/* overloaded operators */
		Sentence &operator=(const Sentence &rightSent);
		Sentence operator+(const Word &rightWord); // sent + word
		Sentence operator++(int); // postfix ++
		Sentence operator--(int); // postfix --
		Sentence &operator++(); // prefix ++
		Sentence &operator--(); // prefix --
		Sentence &operator+(int one);
		/* overloaded << operator */
		friend ostream &operator<<(ostream &out, const Sentence &sentence);
		
	private:
		struct lNode{
			Word data;
			lNode *next;
		};
		lNode *head;
		int listSize;
		char punct;
};

/****------- free floating functions to solve circular dependency -------****/
Sentence operator+(const Word &lhs, const Word &rhs); // word + word
Sentence operator+(const Word &lW, const Sentence &rS); // word + sentence

