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
