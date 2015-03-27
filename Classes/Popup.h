/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Popup.h

Description: Shows up a Sprite as Pause Menu with two buttons
representing Resume Game and Main Menu.
Resume Button - back to Game scene
Main Menu - leave the game and back to Main Menu scene

*/

#ifndef POPUP_H__
#define POPUP_H__

#include "cocos2d.h"

class Popup : public cocos2d::Sprite
{
	/* @brief Pointer to Menu Cocos2D object */
	cocos2d::CCMenu *menu;
public:

	/* @brief init function that initialize the popup class */
	bool init();
	
	/* @brief createPopup function that call functions to create the popup everytime someone click in Pause */
	static Popup* createPopup();
	
	/* @brief show/hide the Pause menu on the screen */
	void show(bool shouldShow, bool);
};

#endif // __POPUP_SPRITE_H__