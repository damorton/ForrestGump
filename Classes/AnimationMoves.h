/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

AnimationMoves.h

Description: Responsible by animate the player and enemies

*/

#ifndef __ANIMATIONMOVES_H__
#define __ANIMATIONMOVES_H__

#include "cocos2d.h"

USING_NS_CC;

class AnimationMoves : public cocos2d::Animate
{
public:
	
	/* @brief init function that Initialize the animation class */
	virtual bool init();

	/* @brief Initialize the parent node */
	CREATE_FUNC(AnimationMoves);

	/* @brief create the instance from this object */
	static AnimationMoves* getInstance();
	
private:
	/* @brief create an AnimationMoves pointer */
	static AnimationMoves* m_spInstance;
};

#endif // __ANIMATIONMOVES_H__
