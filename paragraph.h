#include "sentence.h"

class Paragraph{
	public:
		Paragraph();
		Paragraph(string p);
		Paragraph(const Paragraph &para1); // copy constructor
		void show();
		void addToFront(const Sentence &s1); // add sentence to beginning of paragraph
		void addToBack(const Sentence &s1); // add sentence to end of paragraph
		Sentence first();
		Paragraph rest();
		Paragraph getParagraph();
		~Paragraph();
		/* overloaded operators */
		Paragraph &operator=(const Paragraph &rightPara); // para = para 
		Paragraph operator+(const Paragraph &rightPara); // para + para
		Paragraph operator+(const Sentence &rightSent); // para + sentence
		Paragraph operator++(int); // postfix ++
		Paragraph operator--(int); // postfix --
		Paragraph &operator++(); // prefix ++
		Paragraph &operator--(); // prefix --
		Paragraph &operator+(int one);
		/* overloaded << operator */
		friend ostream &operator<<(ostream &out, const Paragraph &para);
	private:
		struct lNode{
			Sentence data;
			lNode *next;
		};
		lNode *head;

};


Paragraph operator+(const Sentence &lhs, const Sentence &rhs); // sent + sent
Paragraph operator+(const Sentence &lhs, const Paragraph &rhs); // sent + para
