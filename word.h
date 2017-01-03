#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Word{
	public:
		Word();
		Word(string word); // arg constructor
		Word(const Word &word1); // copy constructor
		void show();
		void setWord(string word);
		string getWord();
		void setVal(string s);
		~Word();
		/* overloaded operators */
		Word &operator=(const Word &rightWord); // word = word
		Word operator++(int); // postfix ++
		Word operator--(int); // postfix --
		Word &operator++(); // prefix ++
		Word &operator--(); // prefix --
		Word &operator+(int one);
		/* overloaded << operator **/
		friend ostream &operator<<(ostream &out, const Word &word);
	private:
		string val;
		bool isPigLatin;
		string og;
};

