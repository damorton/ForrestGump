#include <iostream>
#include "CollisionManager.h"
#include "WorldManager.h"
#include "Player.h"
#include "Enemy.h"
#include "GameScene.h"
#include "GameOver.h"


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
	if (!m_vpItems.empty())
	{
		for (std::vector<Sprite*>::size_type it = 0; it < m_vpItems.size(); ++it)
		{
			auto tileSprite = m_vpItems.at(it);
			if (tileSprite)
			{
				if (tileSprite->isVisible())
				{
					if (m_pPlayer->getBoundingBox().intersectsRect(tileSprite->getBoundingBox()))
					{
						if (tileSprite->getName() == "introCoins")
						{
							WorldManager::getInstance()->getPlayer()->addCoin();
						}
						else if (tileSprite->getName() == "coins")
						{
							WorldManager::getInstance()->getPlayer()->addCoin();
						}
						else if (tileSprite->getName() == "items")
						{
							WorldManager::getInstance()->getPlayer()->addItem();
						}
						else if (tileSprite->getName() == "boosters")
						{
							WorldManager::getInstance()->getPlayer()->addBooster();

							// Scale player down
							if (WorldManager::getInstance()->getPlayer()->getScale() > 0.5)
							{
								WorldManager::getInstance()->getPlayer()->setScale(WorldManager::getInstance()->getPlayer()->getScale() - 0.01);
							}
						}
						else if (tileSprite->getName() == "food")
						{
							WorldManager::getInstance()->getPlayer()->addFood();

							// Scale player up
							if (WorldManager::getInstance()->getPlayer()->getScale() < 2.0)
							{
								WorldManager::getInstance()->getPlayer()->setScale(WorldManager::getInstance()->getPlayer()->getScale() + 0.01);
							}
						}
						tileSprite->setVisible(false);
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
		for (std::vector<Enemy*>::size_type it = 0; it < m_vpEnemies.size(); ++it)
		{
			auto enemy = m_vpEnemies.at(it);
			if (enemy)
			{
				if (enemy->isVisible())
				{
					if (m_pPlayer->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
					{
						enemy->setVisible(false);
						if (m_pPlayer->isGod())
						{
							// Woo! I'm invincible!
						}
						else
						{							
							WorldManager::getInstance()->gameLayer()->gameOver();
							
							// need to collect coins and not lose them?
							/*
							if (m_pPlayer->getCoins() < 1)
							{
								
							}
							else
							{
								WorldManager::getInstance()->gameLayer()->addScreenShake();
								m_pPlayer->addParticlesGameObjects("particles/CoinLoss2.plist", m_pPlayer->getContentSize().width, m_pPlayer->getContentSize().height, m_pPlayer->getCoins(), 0.5);
								CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/CoinDrop.wav", false, 0.5, 0.5, 0.5);
								m_pPlayer->resetCoins();
							}
							*/
						}						
					}						
				}
			}
		}
	}
}

void CollisionManager::resetCollisionManager()
{
	m_vpEnemies.clear();
	m_vpItems.clear();	
	CCLOG("Collision Manager reset");
}

void CollisionManager::collisionManagerCleanup()
{	
	m_pPlayer = NULL;
	m_vpEnemies.clear();
	m_vpItems.clear();
	delete m_Instance;
	m_Instance = NULL;
	CCLOG("Collision Manager cleanup");
}