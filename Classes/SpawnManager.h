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
	virtual bool init();
	virtual ~SpawnManager(){};
	void update();
	bool spawnEnemy();
	int getEnemyCount();
	bool addEnemyToActiveVector(Enemy* enemy);
	void resetSprite(Node* sender, void* enemy);
	void moveSprites();
	void resetEnemy(Enemy* enemy);
	void createEnemies();
	void createEnemy(std::string filename, std::string name, Vec2 position, bool gravity, bool rotate);
	CREATE_FUNC(SpawnManager);
private:
	Enemy* m_pGroundEnemy;
	Enemy* m_pFloatingEnemy;
	Enemy* m_pRotatingEnemy;
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;	
	std::vector<Enemy*> m_vpActiveEnemies;
	bool m_bIsSpawned;
};

#endif