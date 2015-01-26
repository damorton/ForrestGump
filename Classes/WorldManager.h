#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include <memory>
#include "Player.h"
#include "Enemy.h"
 
class WorldManager
{
public:
	// typedefs
	typedef std::shared_ptr<Player> spPlayer;
	typedef std::shared_ptr<Enemy> spEnemy;
	
	// member functions	
	virtual bool init();	
	virtual void cleanUp(); 
	
	// getters
	static WorldManager* getInstance(); 
	spPlayer getPlayer(){ return m_pPlayer; };
	spEnemy getEnemy(){ return m_pEnemy; };
	float getGameScale(){ return m_fGameScale; };

	// setters
	void setPlayer(spPlayer player){ m_pPlayer = player; };
	void setEnemy(spEnemy enemy){ m_pEnemy = enemy; };
	void setGameScale(float gameScale){ m_fGameScale = gameScale; };
	
private:
	// private *tors and instance	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 
		
	// member variables
	static WorldManager* m_Instance;
	spPlayer m_pPlayer;
	spEnemy m_pEnemy;

	float m_fGameScale;
	
};

#endif