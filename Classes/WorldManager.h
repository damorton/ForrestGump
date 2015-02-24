#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include "cocos2d.h"
#include "Definitions.h"

#include "Splash.h"
#include "GameScene.h"
#include "HUD.h"

#include "Player.h"
#include "Enemy.h"

#include "DAO/GameDAO.h"

#include <memory>

class WorldManager
{
public:	
	virtual bool init();	
	virtual void cleanUp(); 	
	static WorldManager* getInstance(); 
	static Layer* layerWithTag(int tag);
	static HUD* hudLayer();
	static CollectableFactory* CollectableFactoryLayer();
	static GameScene* gameLayer();	
	void createDAO();

	Player* getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getEnemies(){ return m_vpEnemies; };
	cocos2d::Sprite* getFloorSprite(){ return m_pFloorSprite; };
	std::string getPlayerDistanceScore();
	std::string getPlayerUsername();

	void setPlayer(Player* player){ m_pPlayer = player; };
	void setVectorOfEnemies(std::vector<std::shared_ptr<Enemy>> vectorOfEnemies){ m_vpEnemies = vectorOfEnemies; };
	void setFloorSprite(cocos2d::Sprite* floor){ m_pFloorSprite = floor; };
	void setPlayerDistanceScore(std::string distanceScore);

private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 
	static WorldManager* m_pInstance;
	std::shared_ptr<IGameDAO> m_DataAccessObject;
	Player* m_pPlayer;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies;
	cocos2d::Sprite* m_pFloorSprite;
};

#endif