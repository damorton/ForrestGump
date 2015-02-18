#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"
//#include "WorldManager.h"
#include "Definitions.h"
#include "CollisionManager.h"
#include <iostream>

class SpawnManager : public cocos2d::Layer
{
public:
	/*
	Initialize the SpawnManager layer
	*/
	virtual bool init();
	virtual ~SpawnManager(){};
	void update();
	bool spawnEnemy();
	int getEnemyCount();
	bool addEnemyBehaviour(Enemy* enemy, std::string name);
	void resetSprite(Node* sender, void* enemy);

	/*
	Initialize the parent node
	*/
	CREATE_FUNC(SpawnManager);

private:
	Enemy* m_pGroundEnemy;
	Enemy* m_pFloatingEnemy;
	//std::deque<Enemy*> m_vpEnemies;
	int m_enemyCount = 0; // keep track of number of spawned objects
	
	
	bool m_bIsSpawned;
};

#endif