
FLAGS = -g -Wall -std=c++11

all:	p1

p1:	word.o sentence.o paragraph.o story.o driver.o
	g++ $(FLAGS) word.o sentence.o paragraph.o story.o driver.o -o p1
	
word.o:	word.cpp
	g++ $(FLAGS) -c word.cpp
	
sentence.o:	sentence.cpp
	g++ $(FLAGS) -c sentence.cpp
	
paragraph.o:	paragraph.cpp
	g++ $(FLAGS) -c paragraph.cpp
	
story.o:	story.cpp
	g++ $(FLAGS) -c story.cpp
	
driver.o:	driver.cpp
	g++ $(FLAGS) -c driver.cpp
	
clean:
	rm -f *.o p1
