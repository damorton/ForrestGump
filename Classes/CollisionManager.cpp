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
};

bool CollisionManager::checkCollisons()
{	
	// enemies
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

	// can add checks for wall? bullet? coins?

	// tiles in tilemap
	auto mazeLayer = m_pSegmentLayer->getTileMap()->getLayer("maze");
	Size layerSize = mazeLayer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = mazeLayer->tileAt(Vec2(i, j));
			if (tileSprite)
			{
				tileSprite->setPhysicsBody(PhysicsBody::createBox(Size(tileSprite->getContentSize().width, tileSprite->getContentSize().height)));
				tileSprite->getPhysicsBody()->setDynamic(true);
				tileSprite->getPhysicsBody()->setGravityEnable(false);
				tileSprite->setPosition(Vec2((tileSprite->getPosition().x + tileSprite->getContentSize().width / 2), (tileSprite->getPosition().y + tileSprite->getContentSize().height / 2)));
				if (tileSprite->getBoundingBox().intersectsRect(m_pPlayer->getBoundingBox()))
				{
					tileSprite->setVisible(false);
					return true;
					CCLOG("collision");
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