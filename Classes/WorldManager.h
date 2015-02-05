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
	void setPlayer(Player* player){ m_pPlayer = player; };
private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 		
	static WorldManager* m_pInstance;	
	Player* m_pPlayer;
};

#endif