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
	return true;
}

void Enemy::runAI()
{
	CCLOG("Running Enemy AI");
}

void Enemy::update()
{
	CCLOG("Updating Enemy");
}

void Enemy::cleanUp()
{	CCLOG("Enemy::cleanUp()");

}

// Get Enemy by name and animate
void Enemy::animateEnemy(){
	if (this->getName() == "ground")
	{
		this->getAnimationWithFrames(5, 8, 0);
		this->runAction(animate);
	}
	else if (this->getName() == "floating")
	{
		this->getAnimationWithFrames(9, 12, 1);
		this->runAction(animate);
	}	
}

// Create the Animation Sprites, return animate object
void Enemy::getAnimationWithFrames(int init, int end, int act){

	Vector<SpriteFrame*> animFrames(4);
	char str[100] = { 0 };
	int i = init;
	while (i <= end)
	{
		sprintf(str, "sprites/walk%02dsmall.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 55, 69)); //we assume that the sprites' dimentions are 55*69 rectangles.
		i++;
		animFrames.pushBack(frame);
	}

	//Define number of loops
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	if (act == 1) {
		animation->setLoops(2);
		animation->setDelayPerUnit(1);
	}
	else animation->setLoops(-1);
	animate = Animate::create(animation);
}