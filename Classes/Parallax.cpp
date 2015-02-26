#include "Parallax.h"
#include "Definitions.h"
#include "WorldManager.h"

USING_NS_CC;

bool Parallax::init()
{
	if (!LayerColor::initWithColor(Color4B(173, 216, 230, 255)))
	{
		return false;
	}
	return true;
}

bool Parallax::addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3, const std::string& filename4, const std::string& filename5)
{
	// background 1 - Clouds
	m_pSpriteBackgroundFirst = CCSprite::create(filename1);
	m_pSpriteBackgroundFirst1 = CCSprite::create(filename1);
	m_pSpriteBackgroundFirst->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundFirst1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundFirst, 4);
	this->addChild(m_pSpriteBackgroundFirst1, 4);
	
	// background 2 - Mountains
	m_pSpriteBackgroundSecond = CCSprite::create(filename2);
	m_pSpriteBackgroundSecond1 = CCSprite::create(filename2);
	m_pSpriteBackgroundSecond->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundSecond1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundSecond, 3);
	this->addChild(m_pSpriteBackgroundSecond1, 3);

	// background 3	- Cactos
	m_pSpriteBackgroundThird = CCSprite::create(filename3);
	m_pSpriteBackgroundThird1 = CCSprite::create(filename3);
	m_pSpriteBackgroundThird->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundThird1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundThird, 2);
	this->addChild(m_pSpriteBackgroundThird1, 2);

	// background 4	- Clounds, Sun and Far Mountains
	m_pSpriteBackgroundFourth = CCSprite::create(filename4);
	m_pSpriteBackgroundFourth1 = CCSprite::create(filename4);
	m_pSpriteBackgroundFourth->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundFourth1->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundFourth, 1);
	this->addChild(m_pSpriteBackgroundFourth1, 1);

	// background 5 - floor
	m_pSpriteFloor1 = CCSprite::create(filename5);
	m_pSpriteFloor2 = CCSprite::create(filename5);
	m_pSpriteFloor1->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, m_pSpriteFloor1->getContentSize().height / 2));
	m_pSpriteFloor2->setPosition(Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, m_pSpriteFloor2->getContentSize().height / 2));
	this->addChild(m_pSpriteFloor1, 4);
	this->addChild(m_pSpriteFloor2, 4);
		
	auto floorRect = CCSprite::create(filename5);
	floorRect->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, m_pSpriteFloor1->getContentSize().height / 2));
	this->addChild(floorRect);
	auto floorEdgeBody = PhysicsBody::createEdgeBox(floorRect->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	floorEdgeBody->setDynamic(false);
	floorRect->setPhysicsBody(floorEdgeBody);		
	WorldManager::getInstance()->setFloorSprite(floorRect);

	return true;	
}

void Parallax::update()
{
	m_fSpeed = 3.0f;
	
	scrollBackground(m_pSpriteFloor1, m_pSpriteFloor2, m_fSpeed);
	scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);
	scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, m_fSpeed / 2.0);	
	scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, m_fSpeed / 3.0);
	scrollBackground(m_pSpriteBackgroundFourth, m_pSpriteBackgroundFourth1, m_fSpeed / 5.0);
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

