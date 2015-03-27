/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	CollisionManager.cpp

	Description: Collision manager singleton handles all collisions that occur in game. Each game object
	is registered with the collision manager and checked for collisions against all other active objects in the game.
	The player is checked against each enemy in the active enemy vector, items in the active item vector and power ups.
	When a collision occurs the event triggers the game objects behaviours such as adding a coin to the score of
	being destroyed. 
*/
// Includes
#include <iostream>
#include "audio/include/SimpleAudioEngine.h"
#include "CollisionManager.h"
#include "WorldManager.h"
#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Shield.h"

CollisionManager* CollisionManager::m_Instance = 0;

CollisionManager* CollisionManager::getInstance()
{	
	if (m_Instance == 0)
		m_Instance = new CollisionManager();
	return m_Instance;
}

bool CollisionManager::init()
{		
	m_pWorldManager = WorldManager::getInstance();
	m_pPlayer = m_pWorldManager->getPlayer();
	return true;
}

void CollisionManager::checkCollisions()
{
	// Check collisions with all registerd game objects
	this->checkCollisionsWithItems();
	this->checkCollisionsWithEnemies();
	this->checkCollisionsWithShields();
}

void CollisionManager::checkCollisionsWithItems()
{
	// Loop through the active item vector and check for collisions with the player
	if (!m_vpItems.empty())
	{
		for (std::vector<Sprite*>::size_type it = 0; it < m_vpItems.size(); ++it)
		{
			auto tileSprite = m_vpItems.at(it);
			if (tileSprite)
			{
				if (tileSprite->isVisible())
				{
					// Depending on the name of the item in the vector an event is triggered
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
							// Scale player down to make them smaller in game
							if (m_pPlayer->getScale() > 0.5)
							{
								m_pPlayer->setScale(m_pPlayer->getScale() - 0.01);
								
							}
						}
						else if (tileSprite->getName() == "food")
						{
							m_pPlayer->addFood();

							// Scale player up to increase player size
							if (m_pPlayer->getScale() < 2.0)
							{
								m_pPlayer->setScale(m_pPlayer->getScale() + 0.01);
								
							}
						}
						// If the player collides with an item switch it off
						tileSprite->setVisible(false);
					}
				}
			}
		}
	}
}	


void CollisionManager::checkCollisionsWithEnemies()
{
	// Loop through the active enemy vector and check for collisions with the player
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
						// If the player is in God mode the enemy is destroyed
						enemy->setVisible(false);
						if (m_pPlayer->isGod())
						{
							if (m_pPlayer->getBoundingBox().intersectsRect(enemy->getBoundingBox()))
							{  
								CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0, 1.0, 1.0);
								m_pPlayer->addEnemyDeathParticle();
								// Woo! I'm invincible!
								m_pPlayer->addEnemiesKilled();
						    }
						}
						else
						{					
							// The player is killed and the gaem over scene is loaded
							m_pWorldManager->gameLayer()->gameOver();
							
							// Player will lose all coins if hit by and enemy and will die if coins are 0
							/*
							if (m_pPlayer->getCoins() < 1)
							{
								// Player is dead
								// TODO :: load game over scene
							}
							else
							{
								// TODO : Add screen shake 
								// TODO : reset coins
								// TODO : play sound effect
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
	// Loop through the shields vector and check for collisions with the player
	if (!m_vpShields.empty())
	{
		for (std::vector<Shield*>::size_type it = 0; it < m_vpShields.size(); ++it)
		{
			auto shield = m_vpShields.at(it);
			if (shield)
			{
				// Only check shields that are visible
				if (shield->isVisible())
				{
					if (m_pPlayer->getBoundingBox().intersectsRect(shield->getBoundingBox()))
					{
						// Set the player to GOD MODE!!
						shield->setVisible(false);

						m_pWorldManager->getPlayer()->setGodMode();

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
	//CCLOG("Collision Manager reset");
}

void CollisionManager::collisionManagerCleanup()
{	
	// Clean up the collision manager
	m_pPlayer = NULL; // auto release object
	m_vpEnemies.clear();
	m_vpItems.clear();
	m_vpShields.clear();
	delete m_Instance; // Collision Manager
	m_Instance = NULL;
	//CCLOG("Collision Manager cleanup");
}