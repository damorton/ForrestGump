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