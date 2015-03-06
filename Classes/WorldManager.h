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
	void addUser(std::string username);
	bool isXMLFileExist();
	Player* getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getEnemies(){ return m_vpEnemies; };
	cocos2d::Sprite* getFloorSprite(){ return m_pFloorSprite; };
	std::string getPlayerHighscore();
	std::string getPlayerUsername();
	std::shared_ptr<IGameDAO> getDAO(){ return m_DataAccessObject; };
	void setPlayer(Player* player){ m_pPlayer = player; };
	void setVectorOfEnemies(std::vector<std::shared_ptr<Enemy>> vectorOfEnemies){ m_vpEnemies = vectorOfEnemies; };
	void setFloorSprite(cocos2d::Sprite* floor){ m_pFloorSprite = floor; };
	void setPlayerHighscore(std::string highscore);
	void setGameWorldSpeed(float speed){ m_fWorldSpeed = speed; };
	void getCollectableItemSpeed(float speed){ m_fItemSpeed = speed; };
	float getGameWorldSpeed(){ return m_fWorldSpeed; };
	float getCollectableItemSpeed(){ return m_fItemSpeed; };
private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 
	static WorldManager* m_pInstance;
	std::shared_ptr<IGameDAO> m_DataAccessObject;
	Player* m_pPlayer;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies;
	cocos2d::Sprite* m_pFloorSprite;
	float m_fWorldSpeed;
	float m_fItemSpeed;

};


#endif