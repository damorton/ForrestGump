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
		/*
<<<<<<< HEAD
		sprintf(str, "sprites/walk%02dsmall.png", i);
		auto tempSprite = Sprite::create(str);
		
		auto frame = SpriteFrame::create(str, Rect(0, 0, tempSprite->getContentSize().width, tempSprite->getContentSize().height)); //we assume that the sprites' dimentions are 55*69 rectangles.
		i++;
=======
*/
		sprintf(str, enemyAnimation, i);		
		auto frame = SpriteFrame::create(str, Rect(0, 0, this->getContentSize().width, this->getContentSize().height)); //we assume that the sprites' dimentions are 40*40 rectangles.
//>>>>>>> 8b756a99b26c5845adcae831aaa65284f4048b17
		animFrames.pushBack(frame);
	}	
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);	
	auto animate = Animate::create(animation);	
	auto repeat = RepeatForever::create(animate);
	this->runAction(repeat);
}