
#ifndef COLLISION_H_
#define	COLLISION_H_

#include "cocos2d.h"
#include "CollectableFactory.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Enemy.h"
#include "SpawnManager.h"
#include "Shield.h"

class Enemy;

class CollisionManager
{
public:
	virtual bool init();
	virtual void collisionManagerCleanup();
	static CollisionManager* getInstance();

	void checkCollisions();
	void checkCollisionsWithItems();
	void checkCollisionsWithEnemies();
	void resetCollisionManager();

	void setPlayer(Player* player){ m_pPlayer = player; };
	void addItem(Sprite* item){ m_vpItems.push_back(item); };
	void addEnemy(Enemy* enemy){ m_vpEnemies.push_back(enemy); };
	void addShield(Shield* shield){ m_vpShields.push_back(shield); };

	Player* getPlayer(){ return m_pPlayer; };
	std::deque<Sprite*> getItemsVector(){ return m_vpItems; };
	std::vector<Enemy*> getEnemies(){ return m_vpEnemies; };
	std::vector<Shield*> getShields(){ return m_vpShields; };
	
	void removeItem(){ m_vpItems.pop_front(); };
	void removeEnemy(){ m_vpEnemies.pop_back(); };
	void removeShield(){ m_vpShields.pop_back(); };
	
	

private:	
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; 
	virtual ~CollisionManager(){ this->collisionManagerCleanup(); };
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;
	std::deque<Sprite*> m_vpItems;
	std::vector<Shield*> m_vpShields;
};

#endif