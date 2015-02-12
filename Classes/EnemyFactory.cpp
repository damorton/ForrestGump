#include "EnemyFactory.h"
#include "Enemy.h"

bool EnemyFactory::init()
{
	return true;
}

spEnemy EnemyFactory::createEnemy()
{	
	return spEnemy(new Enemy());
}

void EnemyFactory::cleanUp()
{
}
