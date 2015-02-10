#include <iostream>
#include "CollisionManager.h"
#include "WorldManager.h"
#include "Player.h"
#include "Enemy.h"

CollisionManager* CollisionManager::m_Instance = 0;

CollisionManager* CollisionManager::getInstance()
{	
	if (m_Instance == 0)
		m_Instance = new CollisionManager();
	return m_Instance;
}

bool CollisionManager::init()
{	
	return true;
}

void CollisionManager::registerEnemyWithCollisionManager(std::shared_ptr<Enemy> obj)
{	
	m_vpEnemies.push_back(obj);
}

/*
void CollisionManager::registerSegment(cocos2d::TMXLayer* segment)
{
	m_pSegment = segment;
}
*/

bool CollisionManager::checkCollisions()
{	
	/*
	for (int i = 0; i < (int)m_vpEnemies.size(); i++)
	{		
		if (m_vpEnemies.at(i)->getType() == Character::ENEMY)
		{			
			std::shared_ptr<Enemy> tempEnemy = std::static_pointer_cast<Enemy>(m_vpEnemies.at(i));
			if (m_pPlayer->getBoundingBox().intersectsRect(tempEnemy->getBoundingBox()))
			{
				return true;
			}
		}		
	}
	*/

	// can add checks for wall? bullet? coins?	
	for (int i = 0; i < (int)m_vpSegmentTiles.size(); i++)
	{		
		if (m_pPlayer->getBoundingBox().intersectsRect(m_vpSegmentTiles.at(i)->getBoundingBox()))
		{
			m_vpSegmentTiles.at(i)->setVisible(false);
			return true;
		}
		
	}
	
	return false;
}

void CollisionManager::cleanUp()
{	
	delete m_Instance;
	m_Instance = NULL;
}