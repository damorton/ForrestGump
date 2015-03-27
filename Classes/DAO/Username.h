/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Username.h

	Description: Username is a text item that contains a name and value for use in 
	the XML data access object. The name variable is the element of the XML file the 
	text variable is the value stored at that element
*/

#ifndef _USERNAME_
#define _USERNAME_

// Includes
#include "TextItem.h"

class Username : public TextItem 
{
public:
	Username(){}
	Username(std::string thisText){ setText(thisText.c_str()); setName(""); }
	~Username(){}	
private:
};


#endif