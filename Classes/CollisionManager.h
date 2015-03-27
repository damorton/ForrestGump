
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

	// function to check collisions with shields
	void checkCollisionsWithShields();

	void setPlayer(Player* player){ m_pPlayer = player; };
	void addItem(Sprite* item){ m_vpItems.push_back(item); };
	void addEnemy(Enemy* enemy){ m_vpEnemies.push_back(enemy); };

	// function to add a shield to the vector
	void addShield(Shield* shield){ m_vpShields.push_back(shield); };

	Player* getPlayer(){ return m_pPlayer; };
	std::deque<Sprite*> getItemsVector(){ return m_vpItems; };
	std::vector<Enemy*> getEnemies(){ return m_vpEnemies; };

	// function to return a shield from the vector
	std::vector<Shield*> getShields(){ return m_vpShields; };
	
	void removeItem(){ m_vpItems.pop_front(); };
	void removeEnemy(){ m_vpEnemies.pop_back(); };

	// function to the remove the shield from the vector
	void removeShield(){ m_vpShields.pop_back(); };
	
	

private:	
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; 
	virtual ~CollisionManager(){ this->collisionManagerCleanup(); };
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;
	std::deque<Sprite*> m_vpItems;

	// a vector to hold the shields
	std::vector<Shield*> m_vpShields;

};

#endif