#include "SpawnManager.h"
#include "WorldManager.h"

USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->createEnemies();	
	srand(time(NULL));
	m_bIsSpawned = false;
	return true;
}

void SpawnManager::createEnemies()
{
	// Ground Enemy
	this->createEnemy("sprites/walk05.png", "ground", Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH * 1.2, SCREEN_ORIGIN.y + (WorldManager::getInstance()->getFloorSprite()->getContentSize().height * 2)), true, false);
		
	// Floating Enemies
	this->createEnemy("sprites/walk09small.png", "floating", Vec2(SCREEN_ORIGIN.x + VISIBLE_SIZE_WIDTH * 1.2, SCREEN_ORIGIN.y + getRandomHeight()), false, false);	
}

int SpawnManager::getRandomHeight()
{
	int height;
	height = (rand() % (int)VISIBLE_SIZE_HEIGHT - (int)WorldManager::getInstance()->getFloorSprite()->getContentSize().height) + (int)WorldManager::getInstance()->getFloorSprite()->getContentSize().height;
	return height;
}

void SpawnManager::createEnemy(std::string filename, std::string name, Vec2 position, bool gravity, bool rotate)
{
	auto enemy = Enemy::create(filename);
	enemy->setName(name);
	enemy->setPosition(position);	
	if (enemy->getName() == "ground")
	{
		auto physicsBody = PhysicsBody::createBox(enemy->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		enemy->setPhysicsBody(physicsBody);
		enemy->getPhysicsBody()->setGravityEnable(gravity);
		enemy->getPhysicsBody()->setRotationEnable(rotate);
	}	
	enemy->animateEnemy();
	enemy->setVisible(false);
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

/*
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
*/

void SpawnManager::update()
{
	if (m_vpActiveEnemies.empty())
	{
		m_bIsSpawned = false;
	}
	if (!m_bIsSpawned)
	{
		this->spawnEnemy();
	}
	this->moveSprites();
}

void SpawnManager::moveSprites()
{
	if (!m_vpActiveEnemies.empty())
	{
		for (std::vector<Enemy*>::size_type it = 0; it < m_vpActiveEnemies.size(); ++it)
		{
			auto enemy = m_vpActiveEnemies.at(it);

			if (enemy)
			{
				// move by individual enemy speeds
				enemy->setPosition(Vec2(enemy->getPosition().x - ENEMY_MOVEMENT_SPEED, enemy->getPosition().y));

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
		Enemy* tile = static_cast<Enemy*>(enemy);
		if (tile->getName() == "floating")
		{
			tile->setPosition(Vec2(tile->getPositionX() + (VISIBLE_SIZE_WIDTH * 2), getRandomHeight()));
		}
		else
		{
			tile->setPosition(Vec2(tile->getPositionX() + (VISIBLE_SIZE_WIDTH * 2), tile->getPositionY()));
		}
		tile->setVisible(false);
		enemy->stopAllActions();
		m_vpActiveEnemies.clear();
	}
}
