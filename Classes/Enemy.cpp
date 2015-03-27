/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Enemy.cpp

	Description: Class responsable for create the enemies. There are two mains types of enemies, Flight enemies and Ground enemies.
	This class is also responsable for animate themselves.

*/
// Includes
#include "Enemy.h"

// Create the Enemy object
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

// Enemy Initialization 
bool Enemy::init()
{
	setType(ENEMY);	
	this->getRandomSpeed();
	return true;
}

// Generate a random value to be used as speed movement
void Enemy::getRandomSpeed()
{
	int max = 2;
	int min = 0;
	m_nSpeed = (rand() % max + min);	
}

// TODO : Run Artificial Intelligence algorithm function */
void Enemy::runAI()
{
	//CCLOG("Running Enemy AI");
}

// TODO : Clean up function */
void Enemy::enemyCleanUp()
{	
	//CCLOG("Enemy cleanup");
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

