
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
	void addLayer(TMXLayer* layer){ m_vpLayers.push_back(layer); };
	void addEnemy(Enemy* enemy){ m_vpEnemies.push_back(enemy); };
	void removeEnemy(){ m_vpEnemies.pop_back(); };
	void removeLayer(){ m_vpLayers.pop_front(); };
	void cleanUp();
	Player* getPlayer(){ return m_pPlayer; };
	std::deque<TMXLayer*> getLayers(){ return (std::deque<TMXLayer*>)m_vpLayers; };
	std::vector<Enemy*> getEnemies(){ return m_vpEnemies; };
	void setPlayer(Player* player){ m_pPlayer = player; };	
	void setEnemies(std::vector<Enemy*> enemies){ m_vpEnemies = enemies; };
	void setLayers(std::deque<TMXLayer*> layers){ m_vpLayers = layers; };
private:	
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; 
	~CollisionManager(){ this->cleanUp(); }; 
	Player* m_pPlayer;
	std::deque<TMXLayer*> m_vpLayers;
	std::vector<Enemy*> m_vpEnemies;
};

#endif