#include "Parallax.h"

USING_NS_CC;

Parallax* Parallax::m_spInstance = 0;

Parallax* Parallax::getInstance()
{
	if (m_spInstance == 0)
	{
		m_spInstance = new Parallax();	
	}

	return m_spInstance;
}

bool Parallax::init()
{
	return true;
}

/*
Parallax* Parallax::create2()
{
	// background play layer
	backgroundLayer = Layer::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// background 1 - Clouds and Floor moving
	m_pSpriteBackgroundFirst = CCSprite::create("background/backgroundFirst.png");
	m_pSpriteBackgroundFirst1 = CCSprite::create("background/backgroundFirst.png");
	m_pSpriteBackgroundFirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	m_pSpriteBackgroundFirst1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	backgroundLayer->addChild(m_pSpriteBackgroundFirst, 1); // add child
	backgroundLayer->addChild(m_pSpriteBackgroundFirst1, 1); // add child

	
	// background 2 - Mountains
	m_pSpriteBackgroundSecond = CCSprite::create("background/backgroundSecond.png");
	m_pSpriteBackgroundSecond1 = CCSprite::create("background/backgroundSecond.png");
	m_pSpriteBackgroundSecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	m_pSpriteBackgroundSecond1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	gamePlayLayer->addChild(m_pSpriteBackgroundSecond, -1); // add child
	gamePlayLayer->addChild(m_pSpriteBackgroundSecond1, -1); // add child


	// background 3	- Clounds, Sun and Far Mountains
	m_pSpriteBackgroundThird = CCSprite::create("background/backgroundThird.png");
	m_pSpriteBackgroundThird1 = CCSprite::create("background/backgroundThird.png");
	m_pSpriteBackgroundThird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	m_pSpriteBackgroundThird1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	gamePlayLayer->addChild(m_pSpriteBackgroundThird, -2); // add child
	gamePlayLayer->addChild(m_pSpriteBackgroundThird1, -2); // add child
	
	return true;
}

void Parallax::updateBackground()
{
	m_fSpeed = 5.0f;
	scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);
	scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, (m_fSpeed / 2));
	scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, ((m_fSpeed / 5) - 0.8));
}
*/
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