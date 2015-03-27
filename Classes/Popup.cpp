/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Popup.cpp

Description: Shows up a Sprite as Pause Menu with two buttons
representing Resume Game and Main Menu.
Resume Button - back to Game scene
Main Menu - leave the game and back to Main Menu scene

*/
// Includes
#include "Popup.h"

// init - Initialization function that create popup element
bool Popup::init()
{
	if (!CCSprite::init()) {
		return false;
	}

	// Background Menu	
	auto m = Sprite::create("buttons/menu.png");	

	m->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);	
	this->addChild(m, 1);
	
	// Add menu to my Sprite Pause menu
	this->setVisible(false);
	
	return true;
}

// createPopup - Popup with title, insert text for parameter
Popup* Popup::createPopup()
{
	Popup *pop = new Popup();
	pop->init();
	pop->autorelease();
	return pop;
}

//Shows up a popup screen
void Popup::show(bool shouldShow, bool sel)
{
	// Set my Sprite Pause visible
	this->setVisible(shouldShow);	
}
