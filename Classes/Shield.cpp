// header files included
#include "Shield.h"
#include "WorldManager.h"

// using cocos namespace
USING_NS_CC;

// function  to create the shield
Shield* Shield::create(const std::string& filename)
{
	// creates a shield
	Shield* pSprite = new Shield();

	// creates the shield with the image file that is put in to be used for it
	if (pSprite->initWithFile(filename))
	{
		// calls autorelease to release ownership
		pSprite->autorelease();

		// calls the shields init function
		pSprite->init();

		// returns the created sprite
		return pSprite;

	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

// function to initialise the shield
bool Shield::init()
{
	// sets the type of powerUp to be a shield
	setType(SHIELD);

	// call to function to move the shield
	//this->moveSprite();

	// adds force field sprite to this shield
	this->addSprite();

	// adds the particle to the shield
	this->addParticle();

	// return true
	return true;

}

void Shield::shieldCleanUp()
{

}

void Shield::update()
{

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

	// creates an action to reverse the bezier curve movement
	auto bezierBack = bezierForward->reverse();

	// creates a sequence to move repeat the movement of the shield
	auto rep = RepeatForever::create(Sequence::create(bezierForward, bezierBack, nullptr));

	// adds the action to the shield
	this->runAction(rep);

}

// function to create and add a particle to the shield
void Shield::addParticle()
{
	// creates the particle using the pList
	auto shieldParticle = ParticleSystemQuad::create("particles/shieldPowerUp.plist");

	// sets the position of the particle
	shieldParticle->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);

	// sets the particle to removed when shield is destroyed
	shieldParticle->setAutoRemoveOnFinish(true);

	// sets the rotation of the particle
	shieldParticle->setRotation(360);

	// sets the scale of the particle
	shieldParticle->setScale(0.1);

	// adds the particle to the shield
	this->addChild(shieldParticle);
}

// adds a sprite to the shield
void Shield::addSprite()
{
	// creates a sprite using a png file
	auto outerShield = Sprite::create("sprites/shieldWithSwords.png");

	// sets the position to be at the middle of the shield
	outerShield->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);

	// adds the sprite to the shield object
	this->addChild(outerShield);

}

