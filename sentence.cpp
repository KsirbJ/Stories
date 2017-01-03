#include "sentence.h"

/* Default constuctor */
Sentence::Sentence(){
	head = nullptr;
	listSize = 0;
	punct = '.'; // default end of sentence is a period
	//cout << "called sentence default constructor" << endl;
}

/** Sentence value constructor
 * @param - a string of words to add to the list
 */
Sentence::Sentence(string p){
	//cout << "sentence val constructor" << endl;
	listSize = 0;
	if(p != ""){
		head = new lNode;
		stringstream ssin(p);
		string s;
		lNode *tmp = head; // current
		lNode *l2 = tmp; // previous
		while(ssin >> s){
			char c = s[s.length()-1];
			if(c == '.' || c == '!' || c == '?'){
				s = s.substr(0,s.length()-1);
				punct = c;
			}
			tmp->data.setVal(s);
			tmp->next = new lNode; 
			l2 = tmp;
			tmp = tmp->next;
			listSize++;
		}
		delete l2->next;		// Loop above creates one extra node at the end that is empty.	
		l2->next = nullptr;		// Here it is deleted and set to nullptr instead.
		listSize--;
	}else{
		head = nullptr;
		listSize = 0;
		punct = '.';
	}	
	// fix sentences with no end of sentence punctuation.
	if(punct != '?' && punct != '!'){
		punct = '.'; 
	}
}

/** copy constructor. Creates a deep copy of the other sentence
 * @param - the sentence to copy
 */
Sentence::Sentence(const Sentence &sent1){
	//cout << "called sentence copy constructor" << endl;
	lNode *l1 = nullptr; // current
	lNode *l2 = nullptr; // next
	if(sent1.head == nullptr){
		head = nullptr;
	}else{
		head = new lNode;
		head->data = sent1.head->data;
		l1 = head;
		l2 = sent1.head->next;
		// set up the rest of the nodes
		while(l2 != nullptr){
			l1->next = new lNode;
			l1 = l1->next;
			l1->data = l2->data;
			l2 = l2->next;
		}
		l1->next = nullptr;
	}
	this->listSize = sent1.listSize;
	this->punct = sent1.punct;
}

// print out all the words in the sentence
void Sentence::show(){
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		cout << tmp->data;
	}
}

/* get the first word of the sentence */
Word Sentence::first(){
	//cout << "Sentence::first" << endl;
	Word tmp;
	if(head != nullptr)
		tmp = head->data;
	return tmp;
}

/* get a new sentence minus the first word */
Sentence Sentence::rest(){
	//cout << "Sentence::rest" << endl;
	Sentence tmp;
	for(lNode *ptr = head->next; ptr != nullptr; ptr = ptr->next){
		tmp.addWord(ptr->data.getWord());
	}
	tmp.punct = this->punct;
	return tmp;
}

/** add a word to the end of the linked list
 *  @param the value of the word
 */
void Sentence::addWord(string data){
	//cout << "called Sentence::addWord" << endl;
	lNode *tmp = new lNode;
	tmp->data.setVal(data);
	tmp->next = nullptr;

	// where to put this node
	if(head == nullptr){
		head = tmp;
	}else{
		lNode *last = head;
		while(last->next != nullptr) last = last->next;
		last->next = tmp;
	}
	listSize++;
}

/** add a word to the beggining of the list
 */
void Sentence::addToFront(string data){
	lNode *tmp = new lNode;
	tmp->data.setVal(data);
	if(head == nullptr){
		tmp->next = nullptr;
	}else{
		tmp->next = head;
	}
	head = tmp;
	listSize++;
}

// get the sentnece as a string
string Sentence::getSentence(){
	string sentString = "";
	for(lNode *ptr = head; ptr != nullptr; ptr = ptr->next){
		sentString += ptr->data.getWord() + " ";
	}
	return sentString;
}

// get the sentence object
Sentence Sentence::getActualSentence(){
	Sentence tmp(*this);
	return tmp;
}

// get the end punctuation for the sentence
char Sentence::getPunct() const {
	//cout << "called Sentence::getPunct(). Returning " << punct << endl;
	return punct;
}

/* destructor */
Sentence::~Sentence(){
	//cout << "Sentence destructor" << endl;
	if(head != nullptr){
		lNode *l1 = nullptr; // current
		l1 = head;

		while(l1 != nullptr){
			lNode *l2 = l1->next;
			delete l1;
			l1 = l2;
		}
	}
	
}

/*******---------- overloaded operators -----------*******/

// sent = sent
Sentence & Sentence::operator=(const Sentence &rightSent){
	//cout << "Sentence::operator=" << endl;
	// check if they're the same object
	if(this == &rightSent) return (*this);
	// delete current list
	if(head != nullptr){
		lNode *l1 = nullptr; // current
		l1 = head;
		while(l1 != nullptr){
			lNode *l2 = l1->next; // next
			delete l1;
			l1 = l2;
		}
		head = nullptr;
		punct = '.';
	}
	// create / copy new list
	lNode *l1 = nullptr; // current
	lNode *l2 = nullptr; // next
	if(rightSent.head == nullptr){
		head = nullptr;
	}else{
		head = new lNode;
		head->data = rightSent.head->data;
		l1 = head;
		l2 = rightSent.head->next;
		while(l2 != nullptr){
			l1->next = new lNode;
			l1 = l1->next;
			l1->data = l2->data;

			l2 = l2->next;
		}
		l1->next = nullptr;
		this->listSize = rightSent.listSize;
		this->punct = rightSent.punct;
	}
	
	return (*this);
}

// sent + word
Sentence Sentence::operator+(const Word &rightWord){
	//cout << "Sentence::operator+ third" << endl;
	Word w1(rightWord);
	Sentence tmp(*this);
	tmp.addWord(w1.getWord());
	return tmp;
}

// postfix ++, turn into uppecase
Sentence Sentence::operator++(int){
	//cout << "Sentence::operator++ postfix" << endl;
	Sentence s2(*this);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		tmp->data ++;
	}
	return s2;
}

// postfix --, turn into lowercase
Sentence Sentence::operator--(int){
	//cout << "Sentence::operator-- postfix" << endl;
	Sentence s2(*this);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		tmp->data --;
	}
	return s2;
}

// prefix ++, convert to piglatin
Sentence &Sentence::operator++(){
	//cout << "Sentence::operator++ prefix" << endl;
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		++tmp->data;
	}
	return *this;
}

// prefix --, convert from piglatin
Sentence &Sentence::operator--(){
	//cout << "Sentence::operator-- prefix" << endl;
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		--tmp->data;
	}
	return (*this);
}

// sent + 1, capitilize first letter
Sentence& Sentence::operator+(int one){
	//cout << "Sentence::operator+1" << endl;
	if(one == 1){
		head->data + 1;
	}
	return (*this);
}

// overloaded <<
ostream &operator<<(ostream &out, const Sentence &sentence) {
   //cout << "Sentence operator<<" << endl;
	for(Sentence::lNode *tmp = sentence.head; tmp != nullptr; tmp = tmp->next){
		out << tmp->data;
		if(tmp->next != nullptr){
			out << " " ;
		}
	}
	out << sentence.getPunct() << " ";
   return out;
}


/****------- free floating function to solve circular dependency-------****/

/** word + word. Creates a new sentence with two words
 * @param - the left hand word
 * @param - the right hand word
 */
Sentence operator+(const Word &lhs, const Word &rhs){
	//cout << "called word + word" << endl;
	Word w1(lhs);
	Word w2(rhs);
	Sentence tmp;
	tmp.addWord(w1.getWord());
	tmp.addWord(w2.getWord());
	return tmp;
}

// word + sentence
Sentence operator+(const Word &lW, const Sentence &rS){
	//cout << "called word + sentence" << endl;
	Word w1(lW);
	Sentence s1(rS);
	s1.addToFront(w1.getWord());
	return s1;
}





