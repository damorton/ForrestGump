
#ifndef COLLISION_H_
#define	COLLISION_H_

#include "cocos2d.h"
#include "CollectableFactory.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Enemy.h"
#include "SpawnManager.h"

class Enemy;

class CollisionManager
{
public:
	virtual bool init();
	static CollisionManager* getInstance();	
	void checkCollisions();
	void checkCollisionsWithItems();
	void checkCollisionsWithEnemies();

	void setPlayer(Player* player){ m_pPlayer = player; };
	void addItem(Sprite* item){ m_vpItems.push_back(item); };
	void addEnemy(Enemy* enemy){ m_vpEnemies.push_back(enemy); };

	Player* getPlayer(){ return m_pPlayer; };
	std::deque<Sprite*> getItemsVector(){ return m_vpItems; };
	std::vector<Enemy*> getEnemies(){ return m_vpEnemies; };
	
	void removeItem(){ m_vpItems.pop_front(); };
	void removeEnemy(){ m_vpEnemies.pop_back(); };
	
	void cleanUp();

	
	

private:	
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; 
	~CollisionManager(){ this->cleanUp(); }; 
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;
	std::deque<Sprite*> m_vpItems;
};

#endif