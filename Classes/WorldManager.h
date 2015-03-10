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
	// World Manager
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
	void setFloorSprite(cocos2d::Sprite* floor){ m_pFloorSprite = floor; };
	bool isSoundEnabled(){ return m_bSoundEnabled; };
	void setSoundEnabled(bool sound){ m_bSoundEnabled = sound; };
	void resetGameWorld();

	// Game World
	void increaseGameWorldSpeed(){ m_fWorldSpeed *= GAME_SPEED_INC; };
	void decreaseGameWorldSpeed(){ m_fWorldSpeed /= GAME_SPEED_DEC; };
	float getGameWorldSpeed(){ return m_fWorldSpeed; };
	void setGameWorldSpeed(float speed){ m_fWorldSpeed = speed; };
	Vec2 getGravity(){ return m_GravitationalForce; };
	void setGravity(Vec2 gravity){ m_GravitationalForce = gravity; };
		
	// Player
	Player* getPlayer(){ return m_pPlayer; };
	cocos2d::Sprite* getFloorSprite(){ return m_pFloorSprite; };
	std::string getPlayerHighscore();
	std::string getPlayerUsername();
	void setPlayer(Player* player){ m_pPlayer = player; };		

	// DAO
	std::shared_ptr<IGameDAO> getDAO(){ return m_DataAccessObject; };			
	void setPlayerHighscore(std::string highscore);

	// Enemies
	void increaseEnemyMovementSpeed(){ m_fEnemyMovementSpeed *= GAME_SPEED_INC; };
	void decreaseEnemyMovementSpeed(){ m_fEnemyMovementSpeed /= GAME_SPEED_DEC; };
	float getEnemyMovementSpeed(){ return m_fEnemyMovementSpeed; };
	void setEnemyMovementSpeed(float speed){ m_fEnemyMovementSpeed = speed; };

private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 
	static WorldManager* m_pInstance;
	std::shared_ptr<IGameDAO> m_DataAccessObject;
	Player* m_pPlayer;
	Sprite* m_pShield;
	Sprite* m_pFloorSprite;
	float m_fWorldSpeed;
	float m_fEnemyMovementSpeed;
	Vec2 m_GravitationalForce;
	bool m_bSoundEnabled;
};


#endif