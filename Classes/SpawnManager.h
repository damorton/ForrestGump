#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"
//#include "WorldManager.h"
#include "Definitions.h"


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

	/*
	Initialize the parent node
	*/
	CREATE_FUNC(SpawnManager);

private:
	Enemy* m_pEnemy;
	int m_enemyCount = 0; // keep track of number of spawned objects
};

#endif