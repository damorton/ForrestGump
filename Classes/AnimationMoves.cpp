/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

AnimationMoves.h

Description: Responsible by animate the player and enemies

*/

#include "AnimationMoves.h"

USING_NS_CC;

// initiating the pointer as 0 to create the singleton
AnimationMoves* AnimationMoves::m_spInstance = 0;

// getInstance - return the singleton of AnimationMoves
AnimationMoves* AnimationMoves::getInstance()
{
	if (m_spInstance == 0)
	{
		m_spInstance = new AnimationMoves();
	}

	return m_spInstance;
}

// init - return true as successful to initialize the class
bool AnimationMoves::init()
{	
	return true;
}
