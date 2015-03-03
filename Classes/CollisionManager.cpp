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

void CollisionManager::checkCollisions()
{
	this->checkCollisionsWithItems();
	this->checkCollisionsWithEnemies();
}

void CollisionManager::checkCollisionsWithItems()
{
	if (!m_vpLayers.empty())
	{
		for (std::deque<TMXLayer*>::size_type it = 0; it < m_vpLayers.size(); ++it)
		{
			Size layerSize = m_vpLayers.at(it)->getLayerSize();
			for (int i = 0; i < layerSize.height; i++)
			{
				for (int j = 0; j < layerSize.width; j++)
				{
					auto tileSprite = m_vpLayers.at(it)->tileAt(Vec2(i, j));
					if (tileSprite)
					{
						if (m_pPlayer->getBoundingBox().intersectsRect(tileSprite->getBoundingBox()))
						{
							if (tileSprite->isVisible())
							{
								//CCLOG("Collision detected");
								if (tileSprite->getName() == "coin")
								{
									WorldManager::getInstance()->getPlayer()->addCoin();
								}
								else if (tileSprite->getName() == "item")
								{
									WorldManager::getInstance()->getPlayer()->addItem();
								}
								else if (tileSprite->getName() == "booster")
								{
									WorldManager::getInstance()->getPlayer()->addBooster();
								}
								else if (tileSprite->getName() == "food")
								{
									WorldManager::getInstance()->getPlayer()->addFood();
								}
								tileSprite->setVisible(false);
							}
						}
					}
				}
			}
		}
	}
}

void CollisionManager::checkCollisionsWithEnemies()
{
	if (!m_vpEnemies.empty())
	{
		// loop through the vector and register enemy
		for (std::vector<Enemy*>::size_type it = 0; it < m_vpEnemies.size(); ++it)
		{
			auto enemy = m_vpEnemies.at(it);

			if (enemy)
			{
				if (m_pPlayer->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
				{
					WorldManager::getInstance()->getPlayer()->addCoinLossParticle();
					if (enemy->isVisible())
					{
						//CCLOG("Collision detected");
						if (enemy->getName() == "ground")
						{
							// may use later
						}
						else if (enemy->getName() == "floating")
						{
							// may use later
						}
						enemy->setVisible(false);
					}
				}
			}
		}
	}
}

void CollisionManager::cleanUp()
{	
	m_pPlayer = NULL;
	m_pGroundEnemy = NULL;
	m_pFloatingEnemy = NULL;
	m_vpLayers.clear();
	m_vpEnemies.clear();
}