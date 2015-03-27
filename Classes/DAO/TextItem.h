/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	TextItem.h

	Description: TextItem contains a name and value for use in the XML data access object. 
	The name variable is the element of the XML file the text variable is the value stored at that element
*/

#ifndef _TEXT_ITEM_
#define _TEXT_ITEM_

// Includes
#include <string>

class TextItem 
{
public:
	TextItem(){}
	TextItem(std::string thisText){text = thisText;}
	TextItem(std::string thisText, std::string thisName){ text = thisText; name = thisName; }
	~TextItem(){}

	// Set the text items name and value 
	std::string getText(){return text;}
	std::string getName(){ return name; }
	void setText(const char* newText){text.assign(newText);}	
	void setName(const char* newText){ name.assign(newText); }
private:
	std::string text;	
	std::string name;
};


#endif