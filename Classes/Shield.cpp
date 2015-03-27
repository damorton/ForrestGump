/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.
	Shield.cpp

	Description: implementation for shield object

*/

// Includes
#include "Shield.h"

// create - creates the shield using file
Shield* Shield::create(const std::string& filename)
{
	// creates a shield using the image file, releases ownership of the shield,
	// and calls the init function for the shield
	Shield* pSprite = new Shield();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();

		pSprite->init();

		return pSprite;

	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

// init - function to initialise the shield
bool Shield::init()
{
	setType(SHIELD);

	//this->moveSprite();
	this->addSprite();

	this->addParticle();

	return true;

}

void Shield::shieldCleanUp()
{
	// shield cleanup function
}

void Shield::update()
{
	// update function
}

// function to move the shield
void Shield::moveSprite()
{
	// creates a variable to hold the window sizew
	auto s = Director::getInstance()->getWinSize();

	// creates a bezier curve with 3 control points
	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(this->getPositionX(), s.height / 2);
	bezier.controlPoint_2 = Vec2(this->getPositionX() - 100, s.height / 2);
	bezier.endPosition = Vec2(this->getPositionX() - VISIBLE_SIZE_WIDTH, s.height / 2);

				
	// creates an action to move the shield using the bezier curve created
	auto bezierForward = BezierBy::create(6, bezier);

	// creates an action to reverse the bezier curve movement, creates a sequence to move it
    auto bezierBack = bezierForward->reverse();
	auto rep = RepeatForever::create(Sequence::create(bezierForward, bezierBack, nullptr));
	this->runAction(rep);

}

// function to create and add a particle to the shield
void Shield::addParticle()
{
	// creates the particle using the pList, sets its position, removes particle when shield is destroyed
	auto shieldParticle = ParticleSystemQuad::create("particles/shieldPowerUp.plist");
	shieldParticle->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	shieldParticle->setAutoRemoveOnFinish(true);
	shieldParticle->setRotation(360);
	shieldParticle->setScale(0.1);
	this->addChild(shieldParticle);
}

// adds a sprite to the shield
void Shield::addSprite()
{
	// creates a sprite using a png file, sets its position & adds it to shield
	auto outerShield = Sprite::create("sprites/shieldWithSwords.png");
	outerShield->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(outerShield);

}

