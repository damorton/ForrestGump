#include "Enemy.h"

bool Enemy::init()
{
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
{
#ifdef _DEBUG
	CCLOG("Enemy::cleanUp()");
#endif
}