#ifndef __ANIMATIONMOVES_H__
#define __ANIMATIONMOVES_H__

#include "cocos2d.h"

USING_NS_CC;

class AnimationMoves : public cocos2d::Animate
{
public:
	
	//Initialize the Animation class	
	virtual bool init();
	CREATE_FUNC(AnimationMoves);

	static AnimationMoves* getInstance();
	static Animate* getAnimationWithFrames(int from, int to);
	//void getAnimationWithFrames(int from, int to);

private:
	static AnimationMoves* m_spInstance;
	

};

#endif // __ANIMATIONMOVES_H__
