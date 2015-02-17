#include "SpawnManager.h"


USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setPosition(Vec2(VISIBLE_SIZE_WIDTH, Director::getInstance()->getVisibleOrigin().y));	
	return true;
}

void SpawnManager::update()
{
	this->spawnEnemy();
}


/*

	This function checks the current enemy count if it
	is less than the counter it spawns an enemy

*/
bool SpawnManager::spawnEnemy()
{

	if (m_enemyCount > ENEMY_SPAWN_COUNT) // setting the count at 5 for now, we can increase this with difficulty
	{
		CCLOG("Cant spawn enemy max count reached");

		return false;
	}

	else
	{
		m_pEnemy->spawnEnemy(this);
		m_enemyCount++; // increment the counter as we have spawned an enemy
		//int count = this->getEnemyCount(); // getting the current enemy count
		return true;
	}

}


/*
	This function gives us the current enemy count
*/
int SpawnManager::getEnemyCount()
{
	return m_enemyCount;
}
