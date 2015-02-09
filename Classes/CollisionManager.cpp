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

void CollisionManager::registerSegment(cocos2d::TMXLayer* layer)
{
	m_pMazeLayer = layer;	
}

bool CollisionManager::checkCollisons()
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

	if (m_pMazeLayer != NULL)
	{
		// tiles in tilemap layer "maze"
		for (int i = 0; i < m_pMazeLayer->getLayerSize().height; i++)
		{
			for (int j = 0; j < m_pMazeLayer->getLayerSize().width; j++)
			{
				auto tileSprite = m_pMazeLayer->tileAt(Vec2(i, j));
				if (tileSprite)
				{					
					if (tileSprite->getBoundingBox().intersectsRect(m_pPlayer->getBoundingBox()))
					{
						tileSprite->setVisible(false);
						return true;
						CCLOG("collision");
					}
				}
			}
		}
	}
	return false;
}

void CollisionManager::cleanUp()
{	
	delete m_Instance;
	m_Instance = NULL;
}