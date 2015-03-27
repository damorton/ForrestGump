/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Splash.h

	Description: Creates splash scene which is the intro scene for Grand Theft Muffins

*/

#ifndef SPLASH_H
#define SPLASH_H

// Includes
#include "cocos2d.h"

class Splash : public cocos2d::Layer
{
public:	

	// Create scene 
	static cocos2d::Scene* createScene();

	// Init function t
	virtual bool init();

	// Selector Callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// Implement the "static create()" method manually 
	CREATE_FUNC(Splash);

private:
	// Function to go to main menu 
	void goToMainMenuScene(float dt);
};

#endif // __Splash_SCENE_H__

