#include "Shield.h"
#include "WorldManager.h"

USING_NS_CC;

Shield* Shield::create(const std::string& filename)
{
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

bool Shield::init()
{
	setType(SHIELD);
	this->moveSprite();
	this->addSprite();
	this->addParticle();
	return true;

}

void Shield::shieldCleanUp()
{
	
}

void Shield::moveSprite()
{
	auto s = Director::getInstance()->getWinSize();

	ccBezierConfig bezier;
	bezier.controlPoint_1 = Vec2(0, s.height / 2);
	bezier.controlPoint_2 = Vec2(100, -s.height / 2);
	bezier.endPosition = Vec2(100, 100);

	auto bezierForward = BezierBy::create(3, bezier);
	auto bezierBack = bezierForward->reverse();
	auto rep = RepeatForever::create(Sequence::create(bezierForward, bezierBack, nullptr));

	this->runAction(rep);
}

void Shield::addParticle()
{
	auto shieldParticle = ParticleSystemQuad::create("particles/shieldPowerUp.plist");
	shieldParticle->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
	shieldParticle->setAutoRemoveOnFinish(true);
	shieldParticle->setRotation(360);
	shieldParticle->setScale(0.1);
	this->addChild(shieldParticle);
}

void Shield::addSprite()
{
	auto outerShield = Sprite::create("sprites/shieldWithSwords.png");
	outerShield->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->addChild(outerShield);
	
}