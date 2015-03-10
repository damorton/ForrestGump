#include "Enemy.h"
#include "WorldManager.h"
#include "Definitions.h"

USING_NS_CC;

Enemy* Enemy::create(const std::string& filename)
{
	Enemy* pSprite = new Enemy();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		pSprite->init();
		return pSprite;
	}
	

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool Enemy::init()
{
	setType(ENEMY);	
	/*
	auto movementParticle = CCParticleSystemQuad::create("particles/enemyMovement.plist");
	movementParticle->setPosition(this->getPosition());
	movementParticle->setAutoRemoveOnFinish(true);
	this->addChild(movementParticle, 0, "movement");
	*/
	this->getRandomSpeed();
	return true;
}

void Enemy::getRandomSpeed()
{
	int max = 3;
	int min = 0;
	m_nSpeed = (rand() % max + min);	
}

void Enemy::runAI()
{
	CCLOG("Running Enemy AI");
}

void Enemy::update()
{
	
}

void Enemy::cleanUp()
{	

}

// Get Enemy by name and animate
void Enemy::animateEnemy(){
	if (this->getName() == "ground")
	{
		this->getAnimationWithFrames("sprites/ground%02d.png", 4);
	}
	else if (this->getName() == "floating")
	{
		this->getAnimationWithFrames("sprites/floating%02d.png", 4);
	}	
}

// Create the Animation Sprites, return animate object
void Enemy::getAnimationWithFrames(char* enemyAnimation, int frames){

	Vector<SpriteFrame*> animFrames(4);
	char str[100] = { 0 };	
	for (int i = 1; i < frames; i++)
	{
		sprintf(str, enemyAnimation, i);		
		auto frame = SpriteFrame::create(str, Rect(0, 0, this->getContentSize().width, this->getContentSize().height)); //we assume that the sprites' dimentions are 40*40 rectangles.
		animFrames.pushBack(frame);
	}	
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);	
	auto animate = Animate::create(animation);	
	auto repeat = RepeatForever::create(animate);
	this->runAction(repeat);
}