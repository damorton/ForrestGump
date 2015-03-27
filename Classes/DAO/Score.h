/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

	Score.h

	Description: Score is a text item that contains a name and value for use in 
	the XML data access object. The name variable is the element of the XML file the 
	text variable is the value stored at that element
*/

#ifndef _SCORE_
#define _SCORE_
#include "TextItem.h"

class Score : public TextItem
{
public:
	Score(){}
	Score(std::string thisText){setText(thisText.c_str());}
	Score(std::string thisText, std::string thisName){ setText(thisText.c_str()); setName(thisName.c_str()); }
	~Score(){}	
private:	
};


#endif