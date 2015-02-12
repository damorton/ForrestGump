#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include "cocos2d.h"
#include "Definitions.h"

#include "SplashScene.h"
#include "GameScene.h"
#include "HUD.h"

#include "Player.h"
#include "Enemy.h"

#include <memory>

class WorldManager
{
public:	
	virtual bool init();	
	virtual void cleanUp(); 	
	static WorldManager* getInstance(); 
	static HUD* hudLayer();
	static GameScene* gameLayer();
	static CCLayer* layerWithTag(int tag);

	Splash* getSplashScene(){ return m_cSplashScene; };
	Player* getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getEnemies(){ return m_vpEnemies; };
	cocos2d::Sprite* getFloorSprite(){ return m_pFloorSprite; };	
	void setSplashScene(Splash* splash){ m_cSplashScene = splash; };
	void setPlayer(Player* player){ m_pPlayer = player; };
	void setVectorOfEnemies(std::vector<std::shared_ptr<Enemy>> vectorOfEnemies){ m_vpEnemies = vectorOfEnemies; };
	void setFloorSprite(cocos2d::Sprite* floor){ m_pFloorSprite = floor; };
protected:	
	Splash* m_cSplashScene;	
	Player* m_pPlayer;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies;
	cocos2d::Sprite* m_pFloorSprite;
private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 
	static WorldManager* m_pInstance;
};

#endif