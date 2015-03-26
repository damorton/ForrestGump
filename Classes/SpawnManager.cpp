#include "SpawnManager.h"
#include "WorldManager.h"
#include "Shield.h"
USING_NS_CC;

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
	CCLOG("Spawn Manager init");
	return true;
}

void SpawnManager::spawnManagerCleanup()
{
	m_pPlayer = NULL;
	m_vpEnemies.clear();
	m_vpActiveEnemies.clear();
	m_vpShields.clear();
	m_vpActiveShields.clear();
	CCLOG("Spawn Manager cleanup");
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

bool SpawnManager::spawnEnemy()
{	
	int randomnumber;
	int numberOfEnemies = CollisionManager::getInstance()->getEnemies().size();	
	randomnumber = (rand() % numberOfEnemies);	
	this->addEnemyToActiveVector(CollisionManager::getInstance()->getEnemies().at(randomnumber));	
	m_bIsSpawned = true;
	return true;
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
}

// function to create a shield from a filename, set the shield to have gravity or not and set it to be able to rotate or not
void SpawnManager::createShield(std::string filename, bool gravity, bool rotate)
{
	// creates a shield from filename sent in
	auto shield = Shield::create(filename);

	// sets the shields position
	shield->setPosition(Vec2(VISIBLE_SIZE_WIDTH, VISIBLE_SIZE_HEIGHT/2));

	// adds the shield 
	this->addChild(shield);

	// adds the shield to the collision manager
	CollisionManager::getInstance()->addShield(shield);
}

// function to create shields
void SpawnManager::createShields()
{
	// calls create shield and passes in the arguments to create the shield
	this->createShield("sprites/shieldSmaller.png", true, false);
}

// function to spawn shields
bool SpawnManager::spawnShield()
{
	// variable for random number
	int randomnumber;

	// variable for number of shields which = the amount of shields in the vector in collision manager
	int numberOfShields = CollisionManager::getInstance()->getShields().size();

	// random number calculated from value got from number of shields
	randomnumber = (rand() % numberOfShields);

	// adds a shield at random number
	this->addShieldToActiveVector(CollisionManager::getInstance()->getShields().at(randomnumber));

	// sets the shield is spawned to true
	m_bIsShieldSpawned = true;

	return true;
}

// function to add shield to active vector
bool SpawnManager::addShieldToActiveVector(Shield* shield)
{
	// set shield is visible to true
	shield->setVisible(true);

	// pushed shield onto the vector m_vpActiveShields
	m_vpActiveShields.push_back(shield);

	return true;
}

// function to move the shields
void SpawnManager::moveShields()
{
	// if the vector in returned by getShields is not empty
	if (!CollisionManager::getInstance()->getShields().empty())
	{
		// loop through the vector
		for (std::vector<Enemy*>::size_type it = 0; it < CollisionManager::getInstance()->getShields().size(); ++it)
		{
			// create a shield 
			auto shield = CollisionManager::getInstance()->getShields().at(it);

			if (shield)
			{
				
				// move the shields to move across screen using Enemy movement speed
				shield->setPosition(Point(shield->getPosition().x - WorldManager::getInstance()->getEnemyMovementSpeed(), shield->getPosition().y));

				// if the shield goes off the screen 
				if (shield->getPosition().x < SCREEN_ORIGIN.x - shield->getContentSize().width / 2)
				{
					// reset the shield
					this->resetShield(shield);
				}
			}
		}
	}
}

// function to reset the shield
void SpawnManager::resetShield(Shield* shield)
{
	// if the shield exist i.e does not = null
	if (shield != NULL)
	{
		// create pointer to shield to = cast to shield vector
		Shield* shieldSprite = static_cast<Shield*>(shield);
		
		// reset the sprite position to random x position and half the height
		shieldSprite->setPosition(Vec2(this->getRandomXPos(), VISIBLE_SIZE_HEIGHT / 2));
		
		// set visible to true
		shieldSprite->setVisible(true);
	}
}
