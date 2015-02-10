#include "Parallax.h"

USING_NS_CC;

Parallax* Parallax::m_pInstance = 0;

Parallax* Parallax::getInstance()
{
	if (m_pInstance == 0)
	{
		m_pInstance = new Parallax();
	}
	return m_pInstance;
}

bool Parallax::init()
{
	return true;
}

void Parallax::scrollBackground(Sprite* bck1, Sprite* bck2, float speed)
{
	bck1->setPosition(Vec2(bck1->getPosition().x - speed, bck1->getPosition().y));
	bck2->setPosition(Vec2(bck2->getPosition().x - speed, bck2->getPosition().y));

	if (bck1->getPosition().x < -bck1->getContentSize().width / 2){
		bck1->setPosition(Vec2(bck2->getPosition().x + bck2->getContentSize().width, bck1->getPosition().y));
	}
	if (bck2->getPosition().x < -bck2->getContentSize().width / 2){
		bck2->setPosition(Vec2(bck1->getPosition().x + bck1->getContentSize().width, bck2->getPosition().y));
	}
}