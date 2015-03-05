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

									if (WorldManager::getInstance()->getPlayer()->getScale() > 0.5)
									{
										WorldManager::getInstance()->getPlayer()->setScale(WorldManager::getInstance()->getPlayer()->getScale() - 0.01);
									}


								}
								else if (tileSprite->getName() == "food")
								{
									WorldManager::getInstance()->getPlayer()->addFood();

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
					//enemy->setState(Enemy::DEAD);
					
					if (enemy->isVisible())
					{
						enemy->setVisible(false);
						if (m_pPlayer->getCoins() < 1)
						{
							WorldManager::getInstance()->gameLayer()->gameOver();
						}
						else
						{
							m_pPlayer->addCoinLossParticle();
							m_pPlayer->resetCoins();
						}
						//CCLOG("Collision detected");
						if (enemy->getName() == "ground")
						{
							//gameOver();
						}
						else if (enemy->getName() == "floating")
						{
							//gameOver();
						}
						
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


/*
	On game over we call the game over scene
*/
void CollisionManager::gameOver()
{
	CCLOG("GameOver");
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);
}