#include "SpawnManager.h"
#include "WorldManager.h"

USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initEnemies();
	
	return true;
}

bool SpawnManager::initEnemies()
{
	/*
	Creating enemies
	*/
	m_pGroundEnemy = Enemy::create("sprites/walk05.png");
	m_pGroundEnemy->setName("ground");
	m_pFloatingEnemy = Enemy::create("sprites/Enemy.png");
	m_pFloatingEnemy->setName("floating");
	m_pRotatingEnemy = Enemy::create("sprites/Enemy3.png");
	m_pRotatingEnemy->setName("rotating");

	/*
	Setting enemy positions
	*/
	m_pGroundEnemy->setPosition(Vec2(m_pGroundEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, SCREEN_ORIGIN.y + (WorldManager::getInstance()->getFloorSprite()->getContentSize().height + m_pGroundEnemy->getContentSize().height / 2)));
	m_pFloatingEnemy->setPosition(Vec2(m_pFloatingEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, SCREEN_ORIGIN.y + 100));
	m_pRotatingEnemy->setPosition(Vec2(m_pRotatingEnemy->getPositionX() + VISIBLE_SIZE_WIDTH * 1.5, VISIBLE_SIZE_HEIGHT / 3));

	/*
	Assigning enemies physics properties
	*/
	auto groundEnemyPhysicsBody = PhysicsBody::createBox(m_pGroundEnemy->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	m_pGroundEnemy->setPhysicsBody(groundEnemyPhysicsBody);
	groundEnemyPhysicsBody->setDynamic(false);

	m_pGroundEnemy->setPhysicsBody(PhysicsBody::createBox(Size(m_pGroundEnemy->getContentSize().width, m_pGroundEnemy->getContentSize().height)));
	m_pGroundEnemy->getPhysicsBody()->setDynamic(true);
	m_pGroundEnemy->getPhysicsBody()->setGravityEnable(false);
	m_pGroundEnemy->getPhysicsBody()->setRotationEnable(false);

	auto floatingEnemyPhysicsBody = PhysicsBody::createBox(m_pFloatingEnemy->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	m_pFloatingEnemy->setPhysicsBody(floatingEnemyPhysicsBody);
	floatingEnemyPhysicsBody->setDynamic(false);

	m_pFloatingEnemy->setPhysicsBody(PhysicsBody::createBox(Size(m_pFloatingEnemy->getContentSize().width, m_pFloatingEnemy->getContentSize().height)));
	m_pFloatingEnemy->getPhysicsBody()->setDynamic(true);
	m_pFloatingEnemy->getPhysicsBody()->setGravityEnable(false);
	m_pFloatingEnemy->getPhysicsBody()->setRotationEnable(false);

	auto rotatingEnemyPhysicsBody = PhysicsBody::createBox(m_pRotatingEnemy->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	m_pRotatingEnemy->setPhysicsBody(rotatingEnemyPhysicsBody);
	rotatingEnemyPhysicsBody->setDynamic(false);

	m_pRotatingEnemy->setPhysicsBody(PhysicsBody::createBox(Size(m_pRotatingEnemy->getContentSize().width, m_pRotatingEnemy->getContentSize().height)));
	m_pRotatingEnemy->getPhysicsBody()->setDynamic(true);
	m_pRotatingEnemy->getPhysicsBody()->setGravityEnable(false);

	this->addChild(m_pGroundEnemy);
	this->addChild(m_pFloatingEnemy);
	this->addChild(m_pRotatingEnemy);

	// adding enemies to the collision manager
	CollisionManager::getInstance()->addEnemy(m_pGroundEnemy);
	CollisionManager::getInstance()->addEnemy(m_pFloatingEnemy);
	CollisionManager::getInstance()->addEnemy(m_pRotatingEnemy);

	srand(time(NULL));
	m_bIsSpawned = false;
	this->spawnEnemy();

	return true;
}

/*
	This function checks the current enemy count if it
	is less than the counter it spawns an enemy
*/
bool SpawnManager::spawnEnemy()
{
	int randomnumber;
	int numberOfEnemies = CollisionManager::getInstance()->getEnemies().size();	
	randomnumber = (rand() % numberOfEnemies);

		switch (randomnumber)
		{
		case 0:
			this->addEnemyBehaviour(m_pGroundEnemy);
			m_pGroundEnemy->animateEnemy();
			break;
		case 1:
			this->addEnemyBehaviour(m_pFloatingEnemy);
			m_pFloatingEnemy->animateEnemy();
			break;
		case 2:
			this->addEnemyBehaviour(m_pRotatingEnemy);
			m_pRotatingEnemy->animateEnemy();
			break;
		default:
			CCLOG("enemy spawn random number unknown");
		}

	return true;
}

bool SpawnManager::addEnemyBehaviour(Enemy* enemy)
{
	if (enemy != NULL && enemy->getName() == "ground" || enemy != NULL && enemy->getName() == "floating")
	{ 		
		auto reset = CCCallFuncND::create(this, callfuncND_selector(SpawnManager::resetSprite), (void*)enemy);
		auto enemeySpriteBehaviour = Sequence::create(
			MoveBy::create(SPRITE_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-(VISIBLE_SIZE_WIDTH * 2), 0)),
			reset,
			NULL);
		enemy->runAction(enemeySpriteBehaviour);
	}	
	else if (enemy != NULL && enemy->getName() == "rotating")
	{
		auto reset = CCCallFuncND::create(this, callfuncND_selector(SpawnManager::resetSprite), (void*)enemy);
		auto enemeySpriteBehaviour = Sequence::create(
			MoveBy::create(SPRITE_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-(VISIBLE_SIZE_WIDTH * 2), 0)), reset, NULL);	
		enemy->runAction(enemeySpriteBehaviour);		
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
		enemy->setState(Enemy::ALIVE);
		m_bIsSpawned = false;
	}
}

void SpawnManager::update()
{
	if (!m_bIsSpawned)
	{
		this->spawnEnemy();
	}
}
