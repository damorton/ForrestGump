/*---------------------------------------------------------------------------
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Splash.h

Description: Creates splash scene which is the intro scene for Grand Theft Muffins

---------------------------------------------------------------------------*/

#ifndef SPLASH_H
#define SPLASH_H

#include "cocos2d.h"

class Splash : public cocos2d::Layer
{
public:	

	/* @brief function to create scene */
	static cocos2d::Scene* createScene();

	/* @brief init function to initialise splash screen */
	virtual bool init();

	// @brief selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	/* @brief implement the "static create()" method manually */
	CREATE_FUNC(Splash);

private:
	/* @brief function to go to main menu */
	void goToMainMenuScene(float dt);
};

#endif // __Splash_SCENE_H__

