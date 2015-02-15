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
	if (!m_vpSegmentLayers.empty())
	{
		for (std::vector<TMXLayer*>::size_type currentLayer = 0; currentLayer < m_vpSegmentLayers.size(); currentLayer++)
		{
			Size layerSize = m_vpSegmentLayers[currentLayer]->getLayerSize();
			for (int i = 0; i < layerSize.height; i++)
			{
				for (int j = 0; j < layerSize.width; j++)
				{
					auto tileSprite = m_vpSegmentLayers[currentLayer]->tileAt(Vec2(i, j));
					if (tileSprite)
					{
						if (m_pPlayer->getBoundingBox().intersectsRect(tileSprite->getBoundingBox()))
						{
							tileSprite->setVisible(false);
							CCLOG("Collision with tile");
						}
					}
				}
			}
		}
	}
	return true;
}

void CollisionManager::cleanUp()
{	
	delete m_Instance;
	m_Instance = NULL;
}