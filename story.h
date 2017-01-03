#include "paragraph.h"

class Story{
	public:
		Story();
		Story(const Story &story1);
		Story(string filename);
		void show();
		void addToFront(const Paragraph &para1);
		void addToBack(const Paragraph &para1);
		Paragraph first();
		Story rest();
		bool save(string filename);
		~Story();
		/* overloaded operators */
		Story &operator=(const Story &rightStory); // story = story 
		Story operator+(const Story &rightStory); // story + story
		Story operator+(const Paragraph &rightPara); // story + para
		Story operator++(int); // postfix ++
		Story operator--(int); // postfix --
		Story &operator++(); // prefix ++
		Story &operator--(); // prefix --
		Story &operator+(int one);
		/* overloaded << operator */
		friend ostream &operator<<(ostream &out, const Story &story);
	private:
		struct lNode{
			Paragraph data;
			lNode *next;
		};
		lNode *head;
};

Story operator+(const Paragraph &lhs, const Story &rhs); // para + story
