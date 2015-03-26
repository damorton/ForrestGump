#include <iostream>
#include "CollisionManager.h"
#include "WorldManager.h"
#include "Player.h"
#include "Enemy.h"
#include "GameScene.h"
#include "GameOver.h"
#include "audio/include/SimpleAudioEngine.h"

CollisionManager* CollisionManager::m_Instance = 0;

CollisionManager* CollisionManager::getInstance()
{	
	if (m_Instance == 0)
		m_Instance = new CollisionManager();
	return m_Instance;
}

bool CollisionManager::init()
{	
	m_pPlayer = WorldManager::getInstance()->getPlayer();
	return true;
}

void CollisionManager::checkCollisions()
{
	this->checkCollisionsWithItems();
	this->checkCollisionsWithEnemies();
	this->checkCollisionsWithShields();
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
							m_pPlayer->addCoin();
						}
						else if (tileSprite->getName() == "coins")
						{
							m_pPlayer->addCoin();
						}
						else if (tileSprite->getName() == "coinsA")
						{
							m_pPlayer->addCoin();
						}
						else if (tileSprite->getName() == "coinsB")
						{
							m_pPlayer->addCoin();
						}
						else if (tileSprite->getName() == "coinsC")
						{
							m_pPlayer->addCoin();
						}
						else if (tileSprite->getName() == "items")
						{
							m_pPlayer->addItem();
						}
						else if (tileSprite->getName() == "boosters")
						{
							m_pPlayer->addBooster();

							// Scale player down
							if (m_pPlayer->getScale() > 0.5)
							{
								m_pPlayer->setScale(m_pPlayer->getScale() - 0.01);
								
							}
						}
						else if (tileSprite->getName() == "food")
						{
							m_pPlayer->addFood();

							// Scale player up
							if (m_pPlayer->getScale() < 2.0)
							{
								m_pPlayer->setScale(m_pPlayer->getScale() + 0.01);
								
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
							if (m_pPlayer->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
							{  
								CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/orc_dieShorter.wav", false, 1.0, 1.0, 1.0);
								m_pPlayer->addEnemyDeathParticle();
								// Woo! I'm invincible!
								m_pPlayer->addEnemiesKilled();
						    }
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

void CollisionManager::checkCollisionsWithShields()
{
	if (!m_vpShields.empty())
	{
		for (std::vector<Shield*>::size_type it = 0; it < m_vpShields.size(); ++it)
		{
			auto shield = m_vpShields.at(it);
			if (shield)
			{
				if (shield->isVisible())
				{
					if (m_pPlayer->getBoundingBox().intersectsRect(shield->getBoundingBox()))
					{
						shield->setVisible(false);
						WorldManager::getInstance()->getPlayer()->setGodMode();
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
	m_vpShields.clear();
	CCLOG("Collision Manager reset");
}

void CollisionManager::collisionManagerCleanup()
{	
	m_pPlayer = NULL;
	m_vpEnemies.clear();
	m_vpItems.clear();
	m_vpShields.clear();
	delete m_Instance;
	m_Instance = NULL;
	CCLOG("Collision Manager cleanup");
}