#include "story.h"
#include <fstream>

/* default constructor */
Story::Story(){
	//cout << "story default constructor" << endl;
	head = nullptr;
}

// copy constructor
Story::Story(const Story &story1){
	//cout << "called story copy constructor" << endl;
	lNode *l1 = nullptr; // current
	lNode *l2 = nullptr; // next
	if(story1.head == nullptr){
		head = nullptr;
	}else{
		head = new lNode;
		head->data = story1.head->data;
		l1 = head;
		l2 = story1.head->next;
		while(l2 != nullptr){
			l1->next = new lNode;
			l1 = l1->next;
			l1->data = l2->data;

			l2 = l2->next;
		}
		l1->next = nullptr;
	}
	
}

// create a stroy from a file
Story::Story(string filename){
	//cout << "called story from file constructor with " << filename << endl;
	string line;
	ifstream inf;
	try{
		inf.open(filename);
		if(!(inf.peek() == EOF)){ // does the file contain anything?
			head = new lNode;
			lNode *cur = head;
			lNode *prev = nullptr;

			while(getline(inf, line)){ // get a line

				if(!line.empty() && line != "" && line != "\n"){ // check if empty
					Paragraph p(line);

					cur->data = p; 
					cur->next = new lNode;
					prev = cur;
					cur = cur->next;
				}
			}
			delete prev->next; // creates one extra paragraph. Delete it now.
			prev->next = nullptr;
		}else{
			head = nullptr;
		}
	}catch(...){
		cerr << "Error reading file" << endl;
		head = nullptr;
	}

}

void Story::show(){
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		cout << tmp->data;
	}
}

bool Story::save(string filename){
	//cout << "called story save with " << filename << endl;
	ofstream of;
	of.open(filename);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		of << '\t' << tmp->data << endl;
	}
	of.close();
	return true;
}

// add a paragraph to the beginning of the story
void Story::addToFront(const Paragraph &para1){
	//cout << "called Story::addToFront" << endl;
	lNode *tmp = new lNode;
	tmp->data = para1;
	if(head == nullptr){
		tmp->next = nullptr;
	}else{
		tmp->next = head;
	}
	head = tmp;
}

// add a paragraph to the end of the story
void Story::addToBack(const Paragraph &para1){
	lNode *tmp = new lNode;
	tmp->data = para1;
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

Paragraph Story::first(){
	//cout << "Story::first" << endl;
	Paragraph tmp;
	if(head != nullptr)
		tmp = head->data;
	return tmp;
}

Story Story::rest(){
	//cout << "Story::rest" << endl;
	Story tmp;
	for(lNode *ptr = head->next; ptr != nullptr; ptr = ptr->next){
		tmp.addToBack(ptr->data.getParagraph());
	}
	return tmp;
}

/* destructor */
Story::~Story(){
	//cout << "called story destructor" << endl;
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

/*****------------- overloaded operators ---------------*****/

// story = story
Story& Story::operator=(const Story &rightStory){
	//cout << "Story::operator=" << endl;
	// check if they're the same object
	if(this == &rightStory) return (*this);
	// delete current list
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
	// create / copy new list
	lNode *l1 = nullptr; // current
	lNode *l2 = nullptr; // next
	if(rightStory.head == nullptr){
		head = nullptr;
	}else{
		head = new lNode;
		head->data = rightStory.head->data;
		l1 = head;
		l2 = rightStory.head->next;
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

// story + story
Story Story::operator+(const Story &rightStory){
	//cout << "Story::operator+ 1" << endl;
	Story left(*this);
	Story right(rightStory);
	Story ret;
	for(lNode *tmp = left.head; tmp != nullptr; tmp = tmp->next){
		ret.addToBack(tmp->data);
	}
	for(lNode *tmp = right.head; tmp != nullptr; tmp = tmp->next){
		ret.addToBack(tmp->data);
	}
	return ret;
}

// story + para
Story Story::operator+(const Paragraph &rightPara){
	//cout << "Story::operator+ 2" << endl;
	Story tmp(*this);
	tmp.addToBack(rightPara);
	return tmp;
}

// postfix ++
Story Story::operator++(int){
	//cout << "Story::operator++ postfix" << endl;
	Story s1(*this);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		tmp->data ++;
	}
	return s1;
}

// postfix --
Story Story::operator--(int){
	//cout << "Story::operator-- postfix" << endl;
	Story s1(*this);
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		tmp->data --;
	}
	return s1;
} 

// prefix ++
Story& Story::operator++(){
	//cout << "Story::operator++ prefix" << endl;
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		++tmp->data;
	}
	return (*this);
}

// prefix --
Story& Story::operator--(){
	//cout << "Story::operator-- prefix" << endl;
	for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
		--tmp->data;
	}
	return (*this);
}

// story + 1
Story& Story::operator+(int one){
	//cout << "Story::operator+ 1" << endl;
	if(one == 1){
		for(lNode *tmp = head; tmp != nullptr; tmp = tmp->next){
			tmp->data+1;
		}
	}
	return (*this);
}

/* overloaded << operator */
ostream &operator<<(ostream &out, const Story &story){
	//cout << "Story << operator" << endl;
	for(Story::lNode *tmp = story.head; tmp != nullptr; tmp = tmp->next){
		out << tmp->data << endl;
	}
	return out;
}

/****------- free floating function to solve circular dependency-------****/


// para + story
Story operator+(const Paragraph &lhs, const Story &rhs){
	//cout << "Paragraph::operator+ story" << endl;
	Paragraph p1(lhs);
	Story s2(rhs);
	s2.addToFront(p1);
	return s2;
}
