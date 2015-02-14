#include "AnimationMoves.h"

USING_NS_CC;

AnimationMoves* AnimationMoves::m_spInstance = 0;

AnimationMoves* AnimationMoves::getInstance()
{
	if (m_spInstance == 0)
	{
		m_spInstance = new AnimationMoves();
	}

	return m_spInstance;
}

bool AnimationMoves::init()
{
	return true;
}

//it creates an animation that runs at 24 frames per second
Animate* AnimationMoves::getAnimationWithFrames(int from, int to)
//void AnimationMoves::getAnimationWithFrames(int from, int to)
{
	Animation* anim = Animation::create();


	for (int i = from; i <= to; i++) {
		String *str = String::createWithFormat("sprites/walk%02d.png", i);
		anim->addSpriteFrameWithFile(str->getCString());
	}
	//-1 become our loop repeat forever
	anim->setLoops(-1);
	Animate *animate = Animate::create(anim);
	//this->runAction(RepeatForever::create(animate));
	return animate;
}

/*
//it creates an animation that runs at 24 frames per second
Animate* AnimationMoves::getAnimationWithFrames(int from, int to)
//void AnimationMoves::getAnimationWithFrames(int from, int to)
{	
	Animation* anim = Animation::create();
		

	for (int i = from; i <= to; i++) {
		String *str = String::createWithFormat("sprites/walk%02d.png", i);
		anim->addSpriteFrameWithFile(str->getCString());
	}
	//-1 become our loop repeat forever
	anim->setLoops(-1);
	Animate *animate = Animate::create(anim);
	//this->runAction(RepeatForever::create(animate));
	return animate;
}
*/