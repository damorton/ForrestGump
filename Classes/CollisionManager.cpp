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
		CCLOG("Number of layers in deque: %d", m_vpSegmentLayers.size());
		for (std::deque<TMXLayer*>::size_type it = 0; it < m_vpSegmentLayers.size(); ++it)
		{
			if (m_vpSegmentLayers.at(it) != NULL)
			{
				CCLOG("Checking collisions with tiles on layer: %d", m_vpSegmentLayers.at(it));
				Size layerSize = m_vpSegmentLayers.at(it)->getLayerSize();
				for (int i = 0; i < layerSize.height; i++)
				{
					for (int j = 0; j < layerSize.width; j++)
					{						
						auto tileSprite = m_vpSegmentLayers.at(it)->tileAt(Vec2(i, j));
						if (tileSprite)
						{
							if (m_pPlayer->getBoundingBox().intersectsRect(tileSprite->getBoundingBox()))
							{
								tileSprite->setVisible(false);
								
							}
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