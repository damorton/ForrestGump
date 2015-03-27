

#include "SpawnManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "Shield.h"
#include "Enemy.h"

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->createEnemies();

	// call to create shields
	this->createShields();
	srand(time(NULL));
	m_bIsSpawned = false;

	// sets shield spawned to false 
	m_bIsShieldSpawned = false;
	//CCLOG("Spawn Manager init");
	return true;
}

void SpawnManager::spawnManagerCleanup()
{
	m_pPlayer = NULL;
	m_vpEnemies.clear();
	m_vpActiveEnemies.clear();
	m_vpShields.clear();
	m_vpActiveShields.clear();
	//CCLOG("Spawn Manager cleanup");
}

void SpawnManager::createEnemies()
{
	// Ground Enemy
	this->createEnemy("sprites/ground01.png", "ground", true, false);
	this->createEnemy("sprites/ground01.png", "ground", true, false);
	this->createEnemy("sprites/ground01.png", "ground", true, false);
	// Floating Enemies
	this->createEnemy("sprites/floating01.png", "floating", false, false);		
	this->createEnemy("sprites/floating01.png", "floating", false, false);
	this->createEnemy("sprites/floating01.png", "floating", false, false);	
	this->createEnemy("sprites/floating01.png", "floating", false, false);
	this->createEnemy("sprites/floating01.png", "floating", false, false);
}

int SpawnManager::getRandomHeight()
{	
	int max = (int)SCREEN_ORIGIN.y + VISIBLE_SIZE_HEIGHT * .80;
	int min = (int)SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height * 2;	
	return (rand() % max + min);
}

int SpawnManager::getRandomXPos()
{	
	int max = (int)SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH * 3;
	int min = (int)SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH * 1.2;	
	return (rand() % max + min);
}

// Creates Random X position 
int SpawnManager::getRandomXPosForShield()
{
	int max = (int)SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH * 10;
	int min = (int)SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH * 1.2;
	return (rand() % max + min);
}

void SpawnManager::createEnemy(std::string filename, std::string name, bool gravity, bool rotate)
{
	auto enemy = Enemy::create(filename);
	enemy->setName(name);	
	if (name == "floating")
	{
		enemy->setPosition(Vec2(this->getRandomXPos(), this->getRandomHeight()));
	}
	else if (name == "ground")
	{
		enemy->setPosition(Vec2(this->getRandomXPos(), SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height + enemy->getContentSize().height / 2));
	}	
	enemy->setVisible(true);
	enemy->animateEnemy();
	this->addChild(enemy);
	CollisionManager::getInstance()->addEnemy(enemy);

}

bool SpawnManager::addEnemyToActiveVector(Enemy* enemy)
{
	enemy->setVisible(true);
	m_vpActiveEnemies.push_back(enemy);
	return true;
}

void SpawnManager::update()
{	
	this->moveSprites();

	// call function to move the sprites 
	this->moveShields();
	
}

void SpawnManager::moveSprites()
{
	if (!CollisionManager::getInstance()->getEnemies().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getEnemies().size(); ++it)
		{
			auto enemy = CollisionManager::getInstance()->getEnemies().at(it);

			if (enemy)
			{
				// move by individual enemy speeds
				enemy->setPosition(Vec2(enemy->getPosition().x - (enemy->getSpeed() + WorldManager::getInstance()->getEnemyMovementSpeed()), enemy->getPosition().y));

				if (enemy->getPosition().x < SCREEN_ORIGIN.x - enemy->getContentSize().width / 2){
					this->resetEnemy(enemy);
				}
			}
		}
	}
}

void SpawnManager::resetEnemy(Enemy* enemy)
{
	if (enemy != NULL)
	{
		Enemy* enemySprite = static_cast<Enemy*>(enemy);
		if (enemySprite->getName() == "floating")
		{
			enemySprite->setPosition(Vec2(this->getRandomXPos(), getRandomHeight()));
		}
		else if (enemySprite->getName() == "ground")
		{
			enemySprite->setPosition(Vec2(this->getRandomXPos(), enemySprite->getPositionY()));			
		}
		enemySprite->setVisible(true);		
		enemySprite->getRandomSpeed();
	}
}

void SpawnManager::pauseGame()
{
	if (!CollisionManager::getInstance()->getEnemies().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getEnemies().size(); ++it)
		{
			auto enemy = CollisionManager::getInstance()->getEnemies().at(it);

			if (enemy)
			{
				enemy->pauseSchedulerAndActions();
			}
		}
	}
	if (!CollisionManager::getInstance()->getShields().empty())
	{
		for (std::vector<Shield*>::size_type it = 0; it < CollisionManager::getInstance()->getShields().size(); ++it)
		{
			auto shield = CollisionManager::getInstance()->getShields().at(it);

			if (shield)
			{
				shield->pauseSchedulerAndActions();
			}
		}
	}
}
void SpawnManager::resumeGame()
{
	if (!CollisionManager::getInstance()->getEnemies().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getEnemies().size(); ++it)
		{
			auto enemy = CollisionManager::getInstance()->getEnemies().at(it);

			if (enemy)
			{
				enemy->resumeSchedulerAndActions();
			}
		}
	}
	if (!CollisionManager::getInstance()->getShields().empty())
	{
		for (std::vector<Shield*>::size_type it = 0; it < CollisionManager::getInstance()->getShields().size(); ++it)
		{
			auto shield = CollisionManager::getInstance()->getShields().at(it);

			if (shield)
			{
				shield->resumeSchedulerAndActions();
			}
		}
	}
}

// Create Shield using filename
void SpawnManager::createShield(std::string filename, bool gravity, bool rotate)
{
	// Creates shield, sets its position, and adds it
	auto shield = Shield::create(filename);
	shield->setPosition(Vec2(VISIBLE_SIZE_WIDTH, VISIBLE_SIZE_HEIGHT/2));
    shield->setScale(2.0);
	shield->setPosition(Vec2(this->getRandomXPosForShield(), this->getRandomHeight()));	

	this->addChild(shield);

	// adds the shield to the collision manager
	CollisionManager::getInstance()->addShield(shield);
}

// Create shields
void SpawnManager::createShields()
{
	this->createShield("sprites/shieldSmaller.png", true, false);
}

// Spawn shields
bool SpawnManager::spawnShield()
{
	int randomnumber;

	// variable for number of shields which = the amount of shields in the vector in collision manager
	int numberOfShields = CollisionManager::getInstance()->getShields().size();

	// random number calculated from value got from number of shields
	randomnumber = (rand() % numberOfShields);
	this->addShieldToActiveVector(CollisionManager::getInstance()->getShields().at(randomnumber));
	m_bIsShieldSpawned = true;

	return true;
}

// Add shield to active vector
bool SpawnManager::addShieldToActiveVector(Shield* shield)
{
	shield->setVisible(true);
	m_vpActiveShields.push_back(shield);

	return true;
}

// Move Shields
void SpawnManager::moveShields()
{
	if (!CollisionManager::getInstance()->getShields().empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getShields().size(); ++it)
		{
			auto shield = CollisionManager::getInstance()->getShields().at(it);

			if (shield)
			{				
				// move the shields to move across screen using Enemy movement speed
				shield->setPosition(Point(shield->getPosition().x - WorldManager::getInstance()->getEnemyMovementSpeed(), shield->getPosition().y));
 
				if (shield->getPosition().x < SCREEN_ORIGIN.x - shield->getContentSize().width / 2)
				{
					this->resetShield(shield);
				}
			}
		}
	}
}

//  Reset shield
void SpawnManager::resetShield(Shield* shield)
{
	// if the shield exist i.e does not = null
	if (shield != NULL)
	{
		// create pointer to shield to = cast to shield vector, set position & make visible
		Shield* shieldSprite = static_cast<Shield*>(shield);
		shieldSprite->setPosition(Vec2(this->getRandomXPosForShield(), this->getRandomHeight()));
		shieldSprite->setVisible(true);
	}
}
