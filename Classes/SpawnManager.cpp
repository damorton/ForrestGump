#include "SpawnManager.h"


USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{

		return false;
	}
	
	m_pGroundEnemy = Enemy::create("sprites/Enemy2.png");
	m_pFloatingEnemy = Enemy::create("sprites/Enemy.png");

	m_pGroundEnemy->setPosition(Vec2(m_pGroundEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, 100));
	m_pFloatingEnemy->setPosition(Vec2(m_pFloatingEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, 50));

	this->addChild(m_pGroundEnemy);
	this->addChild(m_pFloatingEnemy);

	srand(time(NULL));
	m_bIsSpawned = false;
	this->spawnEnemy();
	return true;
}

void SpawnManager::update()
{
	if (!m_bIsSpawned)
	{
		this->spawnEnemy();
	}
}


/*

	This function checks the current enemy count if it
	is less than the counter it spawns an enemy

*/
bool SpawnManager::spawnEnemy()
{

	/*
	if (m_enemyCount > ENEMY_SPAWN_COUNT) // setting the count at 5 for now, we can increase this with difficulty
	{
		CCLOG("Cant spawn enemy max count reached");

		return false;
	}

	else
	{
		m_pEnemyGround->spawnEnemy(this);
		m_enemyCount++; // increment the counter as we have spawned an enemy
		//int count = this->getEnemyCount(); // getting the current enemy count
		return true;
	}

	*/

	int randomnumber;
	//int numberOfEnemies = CollisionManager::getInstance()->getEnemies().size();
	int numberOfEnemies = 2;
	randomnumber = (rand() % numberOfEnemies);

	switch (randomnumber)
	{
	case 0:
		this->addEnemyBehaviour(m_pGroundEnemy, "ground");
		break;
	case 1:
		this->addEnemyBehaviour(m_pFloatingEnemy, "floating");
		break;
	default:
		CCLOG("segment spawn random number unknown");
	}
	return true;
}


/*
	This function gives us the current enemy count
*/
int SpawnManager::getEnemyCount()
{
	return m_enemyCount;
}

bool SpawnManager::addEnemyBehaviour(Enemy* enemy, std::string name)
{
	enemy->setName(name);

	if (enemy != NULL)
	{
		// resetin sprite poisition + seeting sprite to invisible
		auto reset = CCCallFuncND::create(this, callfuncND_selector(SpawnManager::resetSprite), (void*)enemy);
		auto enemtySpriteBehaviour = Sequence::create(
			MoveBy::create(SPRITE_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-(VISIBLE_SIZE_WIDTH * 2), 0)),
			reset,
			NULL);
		enemy->runAction(enemtySpriteBehaviour);
	}

	m_bIsSpawned = true;
	return true;
}

void SpawnManager::resetSprite(Node* sender, void* enemyRef)
{
	if (enemyRef != NULL)
	{
		Enemy* enemy = static_cast<Enemy*>(enemyRef);
		enemy->stopAllActions();
		enemy->setPosition(Vec2(enemy->getPositionX() + (VISIBLE_SIZE_WIDTH * 2), enemy->getPositionY()));
		enemy->setVisible(true);
		m_bIsSpawned = false;
	}
}
