/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Popup.h

	Description: Pops up a Sprite pausing the background actions.

*/

#ifndef POPUP_H__
#define POPUP_H__

// Includes
#include "Definitions.h"

class Popup : public cocos2d::Sprite
{
	// Pointer to Menu Cocos2D object 
	cocos2d::CCMenu *menu;
public:

	// Init function that initialize the popup class 
	bool init();
	
	// CreatePopup function that call functions to create the popup everytime someone click in Pause 
	static Popup* createPopup();
	
	// Show/Hide the Pause menu on the screen 
	void show(bool shouldShow, bool);
};

#endif // __POPUP_SPRITE_H__