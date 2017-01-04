#include "word.h"


/* Default constructor */
Word::Word(){
	val = "";
	isPigLatin = false;
	//cout << "called word Default constructor" << endl;
}

// val constructor
Word::Word(string word){
	//cout << "called word val constructor" << endl;
	this->val = word;
	isPigLatin = false;
}

// copy constructor
Word::Word(const Word &word1){
	//cout << "called word copy constructor" << endl;
	this->val = word1.val;
	this->isPigLatin = word1.isPigLatin;
}

void Word::show(){
	//cout << "The word is " << val << endl;
}

// get the value of the word
string Word::getWord(){
	return val;
}

// set the value of the word
void Word::setVal(string s){
	//cout << "called word set val" << endl;
	val = s;
}

/* destructor */
Word::~Word(){
	//cout << "called word destructor" << endl;
	// nothing to do here
}

/**********------------- overloaded operators ------------***********/

// set one word equal to another
Word &Word::operator=(const Word &rightWord){
	//cout << "Word::operator=" << endl;
	val = rightWord.val;
	isPigLatin = rightWord.isPigLatin;
	return (*this);
}

// turn word to uppercase (postfix ++)
Word Word::operator++(int){
	Word w1(*this);
	//cout << "Word::operator++ postfix" << endl;
	for(unsigned int i = 0; i < val.length(); i++){
		this->val[i] = toupper(val[i]);
	}
	return w1;

}

// turn word to lowercase (postfix --)
Word Word::operator--(int){
	Word w1(*this);
	//cout << "Word::operator-- postfix" << endl;
	for(unsigned int i = 0; i < val.length(); i++){
		this->val[i] = tolower(val[i]);
	}
	return w1;
}

// (prefix ++) convert to piglatin
Word &Word::operator++(){
	//cout << "Word::operator++  prefix" << endl;
	if(!isPigLatin){
		Word tmp(val);
		string consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
		string vowels = "aeiouAEIOU"; // assume no y vowel at beginning of word
		string output = "";
		og = val; // store original word
		for (unsigned int i = 0; i < consonants.length(); ++i){
			if(val[0] == consonants[i]){
				if((val[0] == 't' || val[0] == 'T') && (val[1] == 'h' || val[1] == 'H')){ // if th
					output = val.substr(2,val.length()) + "th" + "ay";
				}else if((val[0] == 's' || val[0] == 'S') && (val[1] == 'h' || val[1] == 'H')){ // if sh
					output = val.substr(2,val.length()) + "sh" + "ay";
				}else if((val[0] == 'c' || val[0] == 'C') && (val[1] == 'h' || val[1] == 'H')){ // if ch
					output = val.substr(2,val.length()) + "ch" + "ay";
				}else{
					output = val.substr(1,val.length()) + val[0] + "ay";
				}
			}
		}
		for (unsigned int i = 0; i < vowels.length(); ++i){
			if(val[0] == vowels[i]){
				output = val + "way";
			}
		}
		val = output;
		isPigLatin = true;
	}
	return (*this);
}

// (prefix --) convert from piglatin
Word &Word::operator--(){
	//cout << "Word::operator-- prefix" << endl;
	if(isPigLatin){
		val = og; 
	} 
	isPigLatin = false;
	return (*this);
}

// capitilize the first letter
Word &Word::operator+(int one){
	//cout << "Word::operator+ 1" << endl;
	if(one == 1){
		val[0] = toupper(val[0]);
	}
	return (*this);
}

// print out word
ostream &operator<<(ostream &out, const Word &word){
	out << word.val;
	return out;
}




