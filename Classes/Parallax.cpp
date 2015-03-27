/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Parallax.cpp

	Description: Moves the background images.
*/

// Includes
#include "Parallax.h"
#include "WorldManager.h"

// init - Initialization function
bool Parallax::init()
{
	if (!LayerColor::initWithColor(Color4B(173, 216, 230, 255)))
	{
		return false;
	}

	m_pWorldManager = WorldManager::getInstance();
	return true;
}

// addBackground - Add the backgrounds
bool Parallax::addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3, const std::string& filename4, const std::string& filename5)
{
	// Floor
	m_pSpriteFloor1 = CCSprite::create(filename5);
	m_pSpriteFloor2 = CCSprite::create(filename5);
	m_pSpriteFloor1->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + m_pSpriteFloor1->getContentSize().height / 2));
	m_pSpriteFloor2->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + m_pSpriteFloor2->getContentSize().height / 2));
	this->addChild(m_pSpriteFloor1, 5);
	this->addChild(m_pSpriteFloor2, 5);
	

	// background 1 - Clouds
	m_pSpriteBackgroundFirst = CCSprite::create(filename1);
	m_pSpriteBackgroundFirst1 = CCSprite::create(filename1);
	m_pSpriteBackgroundFirst->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundFirst1->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundFirst, 4);
	this->addChild(m_pSpriteBackgroundFirst1, 4);
	
	// background 2 - Mountains
	m_pSpriteBackgroundSecond = CCSprite::create(filename2);
	m_pSpriteBackgroundSecond1 = CCSprite::create(filename2);
	m_pSpriteBackgroundSecond->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundSecond1->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundSecond, 3);
	this->addChild(m_pSpriteBackgroundSecond1, 3);

	// background 3	- Cactos
	m_pSpriteBackgroundThird = CCSprite::create(filename3);
	m_pSpriteBackgroundThird1 = CCSprite::create(filename3);
	m_pSpriteBackgroundThird->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundThird1->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundThird, 2);
	this->addChild(m_pSpriteBackgroundThird1, 2);

	// background 4	- Clounds, Sun and Far Mountains
	m_pSpriteBackgroundFourth = CCSprite::create(filename4);
	m_pSpriteBackgroundFourth1 = CCSprite::create(filename4);
	m_pSpriteBackgroundFourth->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	m_pSpriteBackgroundFourth1->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT / 2));
	this->addChild(m_pSpriteBackgroundFourth, 1);
	this->addChild(m_pSpriteBackgroundFourth1, 1);
			
	// Floor boundary
	auto floorRect = CCSprite::create();
	floorRect->setContentSize(Size(m_pSpriteFloor1->getContentSize().width * 3, m_pSpriteFloor1->getContentSize().height * .80));
	floorRect->setPosition(Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH / 2, SCREEN_ORIGIN.y + floorRect->getContentSize().height / 2));
	this->addChild(floorRect);
	auto floorEdgeBody = PhysicsBody::createBox(floorRect->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	floorEdgeBody->setDynamic(false);
	floorRect->setPhysicsBody(floorEdgeBody);		
	m_pWorldManager->setFloorSprite(floorRect);

	return true;	
}

// update() - Call the scroll function
void Parallax::update()
{	
	scrollBackground(m_pSpriteFloor1, m_pSpriteFloor2, m_pWorldManager->getGameWorldSpeed());
	scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_pWorldManager->getGameWorldSpeed() / 2.0);
	scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, m_pWorldManager->getGameWorldSpeed() / 3.0);
	scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, m_pWorldManager->getGameWorldSpeed() / 4.0);
	scrollBackground(m_pSpriteBackgroundFourth, m_pSpriteBackgroundFourth1, m_pWorldManager->getGameWorldSpeed() / 5.0);
}

//scrollBackground() - Move background images 
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

void Parallax::parallaxCleanup()
{
	m_pWorldManager = NULL;
	//CCLOG("Parallax cleanup");
}