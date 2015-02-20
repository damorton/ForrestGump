
#ifndef COLLISION_H_
#define	COLLISION_H_

// includes 
#include "cocos2d.h"
#include "CollectableFactory.h"
#include "Player.h"
#include <vector>
#include <memory>
#include "Enemy.h"
#include "SpawnManager.h"

// forward declarations
class Enemy;

class CollisionManager
{
public:
	virtual bool init();
	static CollisionManager* getInstance();	
	void checkCollisions();
	void checkCollisionsWithItems();
	void checkCollisionsWithFloatingEnemy();
	void checkCollisionsWithGroundEnemy();
	void checkCollisionsWithEnemies();
	void addLayer(TMXLayer* layer){ m_vpLayers.push_back(layer); };
	void addEnemy(Enemy* enemy){ m_vpEnemies.push_back(enemy); };
	//void removeEnemy(){ m_vpEnemies.pop_front(); };
	void removeLayer(){ m_vpLayers.pop_front(); };
	void cleanUp();
	Player* getPlayer(){ return m_pPlayer; };
	std::deque<TMXLayer*> getLayers(){ return (std::deque<TMXLayer*>)m_vpLayers; };
	void setPlayer(Player* player){ m_pPlayer = player; };	
	void setEnemies(std::vector<Enemy*> enemies){ m_vpEnemies = enemies; };
	void setLayers(std::deque<TMXLayer*> layers){ m_vpLayers = layers; };
protected:
	Player* m_pPlayer;
	Enemy* m_pGroundEnemy;
	Enemy* m_pFloatingEnemy;
	std::deque<TMXLayer*> m_vpLayers;
	std::vector<Enemy*> m_vpEnemies;

private:
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
};

#endif