#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

//includes
#include <memory>
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include "EnemyFactory.h"
 
class WorldManager
{
public:
	// typedefs
	typedef std::shared_ptr<Player> spPlayer;
	typedef std::shared_ptr<Enemy> spEnemy;
	typedef std::shared_ptr<Boss> spBoss;

	static WorldManager* getInstance(); // WorldManager instance
	virtual bool init();	// initialization
	virtual void cleanUp(); // delete WorldManager and stored objects
	
	// getters
	spPlayer getPlayer(){ return m_pPlayer; }; // player
	spEnemy getEnemy(){ return m_pEnemy; };
	spBoss getBoss(){ return m_pBoss; };	// Boss
	

	// setters
	void setPlayer(spPlayer player){ m_pPlayer = player; };
	void setEnemy(spEnemy enemy){ m_pEnemy = enemy; };
	void setBoss(spBoss Boss){ m_pBoss = Boss; };
	

private:
	static WorldManager* m_Instance; // WorldManager instance
	WorldManager(){ this->init(); }; // constructor 
	~WorldManager(){ this->cleanUp(); }; // deconstructor
		
	// store the Game World objects	
	spPlayer m_pPlayer; // Player
	spEnemy m_pEnemy; // Enemy		
	spBoss m_pBoss; // Boss	
	
};

#endif