/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	WorldManager.h

	Description: The world manager singleton controls the game world and enemy movement speed. It
	also controls the world gravity and allows access to important game objects such as the player, 
	data access objects, and all game scene layers. 
*/
#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

// Includes
#include <memory>
#include "Definitions.h"
#include "DAO/GameDAO.h"

// Forward declarations
class GameScene;
class HUD;
class Player;
class HttpClient;

class WorldManager
{
public:		
	virtual bool init();
	virtual void cleanUp();
	static WorldManager* getInstance();

	// Access to layers
	static Layer* layerWithTag(int tag);
	static HUD* hudLayer();
	static GameScene* gameLayer();

	// Control the game world speed
	void increaseGameWorldSpeed(){ m_fWorldSpeed += GAME_SPEED_INC; };
	void decreaseGameWorldSpeed(){ m_fWorldSpeed -= GAME_SPEED_DEC; };
	float getGameWorldSpeed(){ return m_fWorldSpeed; };
	void setGameWorldSpeed(float speed){ m_fWorldSpeed = speed; };
	void resetGameWorld();

	// Control the game world gravity
	Vec2 getGravity(){ return m_GravitationalForce; };
	void setGravity(Vec2 gravity){ m_GravitationalForce = gravity; };

	// Sound controls and floor sprite access	
	cocos2d::Sprite* getFloorSprite(){ return m_pFloorSprite; };	
	bool isSoundEnabled(){ return m_bSoundEnabled; };
	void setFloorSprite(cocos2d::Sprite* floor){ m_pFloorSprite = floor; };
	void setSoundEnabled(bool sound){ m_bSoundEnabled = sound; };
	
	// Player 
	Player* getPlayer(){ return m_pPlayer; };	
	std::string getPlayerUsername();
	std::string getPlayerHighscore(); // vector index 0
	std::string getNumberOfGamesPlayed(); // vector index 9
	void setUsername(std::string username){ m_strInputUsername = username; };
	void setPlayer(Player* player){ m_pPlayer = player; };

	// DAO
	void createDAO();
	std::shared_ptr<IGameDAO> getDAO(){ return m_DataAccessObject; };
	std::shared_ptr<IGameDAOMySQL> getDAOMySQL(){ return m_DataAccessObjectMySQL; };
	void addUser(std::string username);
	void updateDAO();
	bool isXMLFileExist();

	// HTTP response callback function
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	// Enemy control data
	void increaseEnemyMovementSpeed(){ m_fEnemyMovementSpeed += GAME_SPEED_INC; };
	void decreaseEnemyMovementSpeed(){ m_fEnemyMovementSpeed -= GAME_SPEED_DEC; };
	float getEnemyMovementSpeed(){ return m_fEnemyMovementSpeed; };
	void setEnemyMovementSpeed(float speed){ m_fEnemyMovementSpeed = speed; };

	// Access to the game session time 
	int getTimePlayedSeconds(){ return m_nTimePlayedSeconds; };
	void setTimePlayedSeconds(int secondsPerGame){ m_nTimePlayedSeconds = secondsPerGame; };	

private:	
	WorldManager(){ this->init(); };  
	~WorldManager(){ this->cleanUp(); }; 

	// Private singleton instance
	static WorldManager* m_pInstance;

	// Data access objects
	std::shared_ptr<IGameDAO> m_DataAccessObject;
	std::shared_ptr<IGameDAOMySQL> m_DataAccessObjectMySQL;

	// Cocos2dx auto release objects
	Player* m_pPlayer;
	Sprite* m_pShield;
	Sprite* m_pFloorSprite;
	
	// Game world data
	float m_fWorldSpeed;
	float m_fEnemyMovementSpeed;
	Vec2 m_GravitationalForce;
	bool m_bSoundEnabled;
	int m_nTimePlayedSeconds;

	// Player username used in local XML file when game is fisrt installed
	// TODO : allow user to delete the local XML file and enter a new username
	std::string m_strInputUsername;	
};


#endif