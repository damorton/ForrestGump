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
	// typedefs
	typedef std::shared_ptr<Player> spPlayer;
	typedef std::shared_ptr<Enemy> spEnemy;
	
	virtual bool init();	
	virtual void cleanUp(); 
	
	// getters
	static WorldManager* getInstance(); 
	//spPlayer getPlayer(){ return m_pPlayer; };
	Player* getPlayer(){ return m_pPlayer; };
	spEnemy getEnemy(){ return m_pEnemy; };

	// setters
	void setPlayer(Player* player){ m_pPlayer = player; };
	void setEnemy(spEnemy enemy){ m_pEnemy = enemy; };

	void scaleSpriteToFullScreenSize(Sprite* sprite);

private:
	// private *tors and instance	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 	
	
	static WorldManager* m_Instance;

	Size m_sVisibleSize;
	Vec2 m_vOrigin;

	//spPlayer m_pPlayer;
	Player* m_pPlayer;
	spEnemy m_pEnemy;
	
	
	
};

#endif