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
cocos2d::CCAnimate* AnimationMoves::getAnimationWithFrames(int from, int to)
{
	CCAnimation* anim = CCAnimation::create();

	for (int i = from; i <= to; i++) {
		CCString *str = CCString::createWithFormat("sprites/Playerwalk%02d.png", i);
		anim->addSpriteFrameWithFileName(str->getCString());
	}
	anim->setLoops(-1);
	CCAnimate *animate = CCAnimate::create(anim);
//	animate->setDuration(50.0f);
	return animate;
}