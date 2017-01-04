#include "paragraph.h"

/* Default constructor */
Paragraph::Paragraph(){
	head = nullptr;
	//cout << "paragraph Default constructor" << endl;
}

// value constructor
Paragraph::Paragraph(string p){
	//cout << "paragraph value constructor" << endl;
	if(p != ""){
		head = new lNode;
		istringstream ssin(p);
		string s;
		string s2 = "";
		lNode *cur = head; // current
		lNode *prev = cur; // previous
		while(ssin >> s){
			char c = s[s.length()-1];
			if( c != '.' && c != '!' && c != '?'){ // check for end of sentence punctuation
				s2 = s2 + " " + s;
			}else{
				// found end of sentence, add new sentence to list
				s2 = s2 + " " + s;
				Sentence sent(s2);
				cur->data = sent;
				cur->next = new lNode;
				prev = cur;
				cur = cur->next;
				s2 = "";
			}
		}
		delete prev->next;
		prev->next = nullptr;
	}else{
		head = nullptr;
	}
}

// copy constructor
Paragraph::Paragraph(const Paragraph &para1){
	//cout << "paragraph copy constructor" << endl;
	lNode *l1 = nullptr; // current
	lNode *l2 = nullptr; // next
	if(para1.head == nullptr){
		head = nullptr;
	}else{
		head = new lNode;
		head->data = para1.head->data;
		l1 = head;
		l2 = para1.head->next;
		while(l2 != nullptr){
			l1->next = new lNode;
			l1 = l1->next;
			l1->data = l2->data;

			l2 = l2->next;
		}
		l1->next = nullptr;
	}	
}

// get first sentence in paragraph
Sentence Paragraph::first(){
	//cout << "Paragraph::first" << endl;
	Sentence tmp = head->data;
	return tmp;
}

// get paragraph minus first sentence
Paragraph Paragraph::rest(){
	//cout << "Paragraph::rest" << endl;
	Paragraph tmp;
	for(lNode *ptr = head->next; ptr != nullptr; ptr = ptr->next){
		tmp.addToBack(ptr->data.getActualSentence());
	}
	return tmp;
}

// print out text in paragraph
void Paragraph::show(){
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		cout << tmp->data;
	}
}

// add a sentence to the beginning of the paragraph
void Paragraph::addToFront(const Sentence &s1){
	//cout << "called Paragraph::addToFront" << endl;
	lNode *tmp = new lNode;
	tmp->data = s1;
	if(head == nullptr){
		tmp->next = nullptr;
	}else{
		tmp->next = head;
	}
	head = tmp;
}

// add a sentence to the end of the paragraph
void Paragraph::addToBack(const Sentence &s1){
	lNode *tmp = new lNode;
	tmp->data = s1;
	tmp->next = nullptr;

	// where to put this node
	if(head == nullptr){
		head = tmp;
	}else{
		lNode *last = head;
		while(last->next != nullptr) last = last->next;
		last->next = tmp;
	}

}

// get the paragraph
Paragraph Paragraph::getParagraph(){
	return (*this);
}

/* destructor */
Paragraph::~Paragraph(){
	//cout << "Paragraph destructor" << endl;
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


/*****---------- overloaded operators ----------*****/

// para = para
Paragraph &Paragraph::operator=(const Paragraph &rightPara){
	//cout << "Paragraph::operator=" << endl;
	// check if they're the same object
	if(this == &rightPara) return (*this);

	if(head != nullptr){
		lNode *l1 = nullptr; // current
		l1 = head;
		while(l1 != nullptr){
			lNode *l2 = l1->next;
			delete l1;
			l1 = l2;
		}
		head = nullptr;
	}
	lNode *l1 = nullptr; // current
	lNode *l2 = nullptr; // next
	if(rightPara.head == nullptr){
		head = nullptr;
	}else{
		head = new lNode;
		head->data = rightPara.head->data;
		l1 = head;
		l2 = rightPara.head->next;
		while(l2 != nullptr){
			l1->next = new lNode;
			l1 = l1->next;
			l1->data = l2->data;

			l2 = l2->next;
		}
		l1->next = nullptr;
	}
	
	return (*this);
}

// para + para
Paragraph Paragraph::operator+(const Paragraph &rightPara){
	//cout << "Paragraph::operator+ para" << endl;
	Paragraph left(*this);
	Paragraph right(rightPara);
	Paragraph ret;
	for(lNode *tmp = left.head; tmp != nullptr; tmp = tmp->next){
		ret.addToBack(tmp->data);
	}
	for(lNode *tmp = right.head; tmp != nullptr; tmp = tmp->next){
		ret.addToBack(tmp->data);
	}
	return ret;
}

// para + sent
Paragraph Paragraph::operator+(const Sentence &rightSent){
	//cout << "Paragraph::operator+ sent" << endl;
	Paragraph left(*this);
	left.addToBack(rightSent);
	return left;
}

// postfix ++, make all caps
Paragraph Paragraph::operator++(int){
	//cout << "Paragraph::operator++ postfix" << endl;
	Paragraph p1(*this);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		tmp->data ++;
	}
	return p1;
}

// postfix --, make all lowercase
Paragraph Paragraph::operator--(int){
	//cout << "Paragraph::operator-- postfix" << endl;
	Paragraph p1(*this);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		tmp->data --;
	}
	return p1;
}

// prefix ++, convert to piglatin
Paragraph &Paragraph::operator++(){
	//cout << "Paragraph::operator++ prefix" << endl;
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		++tmp->data;
	}
	return (*this);
}

// prefix --, convert from piglatin
Paragraph &Paragraph::operator--(){
	//cout << "Paragraph::operator-- prefix" << endl;
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		--tmp->data ;
	}
	return (*this);
}

// para + 1, capitilize first word of all sentences
Paragraph& Paragraph::operator+(int one){
	//cout << "Paragraph::operator+1" << endl;
	if(one == 1){
		for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
			tmp->data+1 ;
		}
	}
	return (*this);
}

/* overloaded << operator **/
ostream &operator<<(ostream &out, const Paragraph &para){
	//cout << "Paragraph operator<<" << endl;
	cout << '\t';
	for(Paragraph::lNode *tmp = para.head; tmp != nullptr; tmp = tmp->next){
		out << tmp->data;
	}
	out << endl;
	return out;
}



/****------- free floating function to solve circular dependency-------****/

// sent + sent
Paragraph operator+(const Sentence &lhs, const Sentence &rhs){
	//cout << "Sentence::operator+ first" << endl;
	Sentence s1(lhs);
	Sentence s2(rhs);
	Paragraph tmp;
	tmp.addToBack(lhs);
	tmp.addToBack(rhs);
	return tmp;
}

// sent + para
Paragraph operator+(const Sentence &lhs, const Paragraph &rhs){
	//cout << "Sentence::operator + second" << endl;
	Sentence s1(lhs);
	Paragraph p1(rhs);
	p1.addToFront(lhs);
	return p1;
}
