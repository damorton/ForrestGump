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

bool CollisionManager::checkCollisions()
{	
	if (m_pSegmentManager->isSpawned())
	{
		Size layerSize = m_pSegment->getLayerSize();
		for (int i = 0; i < layerSize.height; i++)
		{
			for (int j = 0; j < layerSize.width; j++)
			{
				auto tileSprite = m_pSegment->tileAt(Vec2(i, j));
				if (tileSprite)
				{
					if (m_pPlayer->getBoundingBox().intersectsRect(tileSprite->getBoundingBox()))
					{	
						tileSprite->removeFromParent();
						CCLOG("Collision with tile");
					}					
				}
			}
		}
	}	
	else
	{
		CCLOG("No segment has been spawned");
	}
	return true;
}

void CollisionManager::cleanUp()
{	
	delete m_Instance;
	m_Instance = NULL;
}