#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#define FONT_SIZE ((visibleSize.width / 1920) * 100)

#include <memory>
#include "Player.h"
#include "Enemy.h"
 
USING_NS_CC;

class WorldManager
{
public:	
	virtual bool init();	
	virtual void cleanUp(); 	
	static WorldManager* getInstance(); 

	Player* getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getEnemies(){ return m_vpEnemies; };
	Sprite* getFloorSprite(){ return m_pFloorSprite; };

	void setPlayer(Player* player){ m_pPlayer = player; };
	void setVectorOfEnemies(std::vector<std::shared_ptr<Enemy>> vectorOfEnemies){ m_vpEnemies = vectorOfEnemies; };
	void setFloorSprite(Sprite* floor){ m_pFloorSprite = floor; };
private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 

	static WorldManager* m_pInstance; // this
	Player* m_pPlayer; // player
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; // vector of enemies
	Sprite* m_pFloorSprite;
};

#endif