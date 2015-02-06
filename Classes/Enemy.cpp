#include "Enemy.h"

Enemy* Enemy::create(const std::string& filename)
{
	Enemy* pSprite = new Enemy();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		pSprite->init();
		//pSprite->addEvents();
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

/*
	Run the enemy AI
*/
void Enemy::runAI()
{
	CCLOG("Running Enemy AI");
}

/*
	Update the enemy
*/
void Enemy::update()
{
	CCLOG("Updating Enemy");
}

/*
	Enemy cleanup
*/
void Enemy::cleanUp()
{	CCLOG("Enemy::cleanUp()");

}