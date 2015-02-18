
#ifndef COLLISION_H_
#define	COLLISION_H_

// includes 
#include "cocos2d.h"
#include "CollectableFactory.h"
#include "Player.h"
#include <vector>
#include <memory>
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
	void addLayer(TMXLayer* layer){ m_vpLayers.push_back(layer); };
	void removeLayer(){ m_vpLayers.pop_front(); };
	void cleanUp();
	Player* getPlayer(){ return m_pPlayer; };
	std::deque<TMXLayer*> getLayers(){ return (std::deque<TMXLayer*>)m_vpLayers; };
	void setPlayer(Player* player){ m_pPlayer = player; };	
	void setLayers(std::deque<TMXLayer*> layers){ m_vpLayers = layers; };
protected:
	Player* m_pPlayer; 		
	std::deque<TMXLayer*> m_vpLayers;
	std::deque<Enemy*> m_vpEnemies;
private:
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
};

#endif