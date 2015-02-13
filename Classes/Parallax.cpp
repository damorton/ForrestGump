#include "Parallax.h"
#include "Definitions.h"

USING_NS_CC;

bool Parallax::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

bool Parallax::addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3)
{
	// background 1 - Clouds and Floor moving
	m_pSpriteBackgroundFirst = CCSprite::create(filename1);
	m_pSpriteBackgroundFirst1 = CCSprite::create(filename1);
	m_pSpriteBackgroundFirst->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundFirst1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundFirst, 1);
	this->addChild(m_pSpriteBackgroundFirst1, 1);
	
	// background 2 - Mountains
	m_pSpriteBackgroundSecond = CCSprite::create(filename2);
	m_pSpriteBackgroundSecond1 = CCSprite::create(filename2);
	m_pSpriteBackgroundSecond->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundSecond1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundSecond, -1);
	this->addChild(m_pSpriteBackgroundSecond1, -1);

	// background 3	- Clounds, Sun and Far Mountains
	m_pSpriteBackgroundThird = CCSprite::create(filename3);
	m_pSpriteBackgroundThird1 = CCSprite::create(filename3);
	m_pSpriteBackgroundThird->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundThird1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundThird, -2);
	this->addChild(m_pSpriteBackgroundThird1, -2);
	
	return true;	
}

void Parallax::updateBackground()
{
	m_fSpeed = 5.0f;
	
	scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);
	scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, (m_fSpeed / 2));
	scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, ((m_fSpeed / 5) - 0.8));
}

void Parallax::scrollBackground(CCSprite* bck1, CCSprite* bck2, float speed)
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

