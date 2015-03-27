/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	WorldManager.cpp

	Description: The world manager singleton controls the game world and enemy movement speed. It
	also controls the world gravity and allows access to important game objects such as the player,
	data access objects, and all game scene layers.
*/
// Includes
#include "WorldManager.h"
#include <iostream>
#include "Player.h"
#include "DAO/User.h"
#include "network\HttpClient.h"

WorldManager* WorldManager::m_pInstance = 0;

WorldManager* WorldManager::getInstance()
{	
	// Return the pointer to the world manager, create 
	// the world manager if it dosen't exist. Singleton.
	if (m_pInstance == 0)
	{
		m_pInstance = new WorldManager();
	}	
	return m_pInstance;
}

bool WorldManager::init()
{	
	// Initialize the game world
	m_fWorldSpeed = WORLD_MOVEMENT_SPEED;
	m_fEnemyMovementSpeed = ENEMY_MOVEMENT_SPEED;
	m_GravitationalForce = GRAVITATIONAL_FORCE;	
	m_nTimePlayedSeconds = 0;
	return true;
}

GameScene* WorldManager::gameLayer()
{
	return (GameScene*)WorldManager::layerWithTag(TAG_GAME_LAYER);
}

HUD* WorldManager::hudLayer()
{
	return (HUD*)WorldManager::layerWithTag(TAG_HUD);
}

Layer* WorldManager::layerWithTag(int tag)
{
	// Return a layer based on the layers tag
	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene->getTag() == TAG_GAME_SCENE) {
		
		// Game scene contains all game layers
		Layer* layer = (Layer*)scene->getChildByTag(tag);
		return layer;
	}
	return NULL;
}

void WorldManager::createDAO()
{
	// XML Data Access Object
	m_DataAccessObject = std::shared_ptr<IGameDAO>(new GameDAO());	

	// Create the DAO if the XML file has not 
	// already been created
	if (!this->isXMLFileExist())
	{		
		m_DataAccessObject->create();
		this->addUser(m_strInputUsername);
	}

	// MySQL Data Access Object
	m_DataAccessObjectMySQL = std::shared_ptr<IGameDAOMySQL>(new GameDAOMySQL());
}

bool WorldManager::isXMLFileExist()
{
	// Check if the XML file exists by getting a writable path
	// based on the device the game is running on.
	std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
	filepath.append(XMLDOC);
	//CCLOG("%s", filepath.c_str());

	// Try and open the file at filepath
	FILE *fp = fopen(filepath.c_str(), "r");
	bool bRet = false;
	
	// If the file can be opened, it exists
	if (fp)
	{
		bRet = true;
		fclose(fp);
	}
	return bRet;
}

void WorldManager::addUser(std::string username)
{
	// Read the XML file and retrieve the vector of users
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();

	// Add user scores to be recorded
	User user;	
	user.setUsername(username.c_str());
	user.addScore("0", "Highscore");
	user.addScore("0", "Distance");
	user.addScore("0", "Coins");
	user.addScore("0", "Items");
	user.addScore("0", "Boosters");
	user.addScore("0", "Food");
	user.addScore("0", "EnemiesKilled");		
	user.addScore("0", "TimePlayed");
		
	// Add user the vector and pass back to the DAO for storing
	users->push_back(user);
	m_DataAccessObject->update(users);
}

void WorldManager::updateDAO()
{
	// XML
	// Read DAO and retrieve vector of users
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();	
	
	// Update users in vector
	// TODO : add more users to the XML file
	users->at(0).getScores()->at(0).setText(std::to_string(m_pPlayer->getHighScore()).c_str());
	users->at(0).getScores()->at(1).setText(std::to_string(m_pPlayer->getDistance()).c_str());
	users->at(0).getScores()->at(2).setText(std::to_string(m_pPlayer->getCoins()).c_str());
	users->at(0).getScores()->at(3).setText(std::to_string(m_pPlayer->getItems()).c_str());
	users->at(0).getScores()->at(4).setText(std::to_string(m_pPlayer->getBoosters()).c_str()); // not recorded in remote db
	users->at(0).getScores()->at(5).setText(std::to_string(m_pPlayer->getFood()).c_str()); // not recorded in remote db
	users->at(0).getScores()->at(6).setText(std::to_string(m_pPlayer->getEnemiesKilled()).c_str());
	users->at(0).getScores()->at(7).setText(std::to_string(m_nTimePlayedSeconds).c_str());
		
	/*
	// Print the contents of the vector of users and scores
	for (int i = 0; i < users->size(); i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}
	*/

	// Update the local XML file
	m_DataAccessObject->update(users);

	// Update Remote MySQL database			
	/*
	cocos2d::network::HttpRequest* remoteRequest = new (std::nothrow) cocos2d::network::HttpRequest();
	remoteRequest->setUrl("http://grandtheftmuffins.esy.es/update_db.php/");
	remoteRequest->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	remoteRequest->setResponseCallback(CC_CALLBACK_2(WorldManager::onHttpRequestCompleted, this));
	*/

	// Construct the request string to update the database
	// TODO : Read the string from the XML file??
	String *remoteData = String::createWithFormat("playerUsername=%s&playerHighscore=%s&playerDistance=%s&playerCoins=%s&enemiesKilled=%s&itemsCollected=%s&timePlayed=%s&numberOfGamesPlayed=1&numberOfDeaths=1", 
		WorldManager::getInstance()->getPlayerUsername().c_str(), 
		std::to_string(m_pPlayer->getHighScore()).c_str(),
		std::to_string(m_pPlayer->getDistance()).c_str(),
		std::to_string(m_pPlayer->getCoins()).c_str(),
		std::to_string(m_pPlayer->getEnemiesKilled()).c_str(),
		std::to_string(m_pPlayer->getItems()).c_str(),
		std::to_string(m_nTimePlayedSeconds).c_str()
		);

	//CCLOG("%s", remoteData->getCString());

	/*
	remoteRequest->setRequestData(remoteData->getCString(), remoteData->length());
	cocos2d::network::HttpClient::getInstance()->send(remoteRequest);
	remoteRequest->release();
	*/	
	
	// Send request string to the MySQL DAO
	m_DataAccessObjectMySQL->update(remoteData->getCString());
}

void WorldManager::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	/*
	//CCLOG("http request completed");
	if (response && response->getResponseCode() == 200 && response->getResponseData()) {
	std::vector<char> *data = response->getResponseData();
	std::string ret(&(data->front()), data->size());
	CCLOG("%s", ("Response message: " + ret).c_str());
	}
	else
	{
	CCLOG("%s", ("Error " + std::to_string(response->getResponseCode()) + " in request").c_str()); //error
	}
	*/
}

std::string WorldManager::getPlayerUsername()
{
	// Player is at vector index 0 because only one player on file
	std::string playerUsername;
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	playerUsername = users->at(0).getUsername()->getText().c_str();
	return playerUsername;
}

std::string WorldManager::getPlayerHighscore()
{
	std::string playerHighScore;
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	playerHighScore = users->at(0).getScores()->at(0).getText().c_str();
	return playerHighScore;
}

std::string WorldManager::getNumberOfGamesPlayed()
{
	// Number of games played information is at index 9
	std::string playerHighScore;
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	playerHighScore = users->at(0).getScores()->at(9).getText().c_str();
	return playerHighScore;
}

void WorldManager::resetGameWorld()
{
	m_fWorldSpeed = WORLD_MOVEMENT_SPEED;
	m_fEnemyMovementSpeed = ENEMY_MOVEMENT_SPEED;
	m_GravitationalForce = GRAVITATIONAL_FORCE;
	//CCLOG("World Manager reset");
}

void WorldManager::cleanUp()
{		
	m_pPlayer = NULL; // Cocos2dx auto release object
	m_pFloorSprite = NULL; // Cocos2dx auto release object
	m_pShield = NULL; // Cocos2dx auto release object
	m_DataAccessObject = NULL; // shared pointer
	m_DataAccessObjectMySQL = NULL; // shared pointer
	delete m_pInstance; // World Manager instance
	m_pInstance = NULL;
}
