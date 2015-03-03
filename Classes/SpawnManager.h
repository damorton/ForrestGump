#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"
#include "Definitions.h"
#include "CollisionManager.h"
#include "Player.h"
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
	void spawnEnemy(float dt);
	int getEnemyCount();
	int getPlayerDistance(); // used to adjust enemy spawns
	void setSpawnFreq(int dist);
	bool addEnemyBehaviour(Enemy* enemy, std::string name);
	void resetSprite(Node* sender, void* enemy);

	/*
	Initialize the parent node
	*/
	CREATE_FUNC(SpawnManager);

private:
	Enemy* m_pGroundEnemy;
	Enemy* m_pFloatingEnemy;
	Enemy* m_pRotatingEnemy;
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;
	//int m_enemyCount = 0; // keep track of number of spawned objects

	float spawnFrequency = 0.0029f;
	
	
	bool m_bIsSpawned;
};

#endif