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

	std::shared_ptr<Player> getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getEnemies(){ return m_vpEnemies; };

	void setPlayer(std::shared_ptr<Player> player){ m_pPlayer = player; };
	void setVectorOfEnemies(std::vector<std::shared_ptr<Enemy>> vectorOfEnemies){ m_vpEnemies = vectorOfEnemies; };
private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 

	static WorldManager* m_pInstance; // this
	std::shared_ptr<Player> m_pPlayer; // player
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; // vector of enemies
};

#endif