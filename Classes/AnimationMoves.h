#ifndef __ANIMATIONMOVES_H__
#define __ANIMATIONMOVES_H__

#include "cocos2d.h"

USING_NS_CC;

class AnimationMoves
{
public:
	/*
	Initialize the Animation class
	*/
	virtual bool init();

	static AnimationMoves* getInstance();
	static cocos2d::CCAnimate* getAnimationWithFrames(int from, int to);

private:
	static AnimationMoves* m_spInstance;
	

};

#endif // __ANIMATIONMOVES_H__
