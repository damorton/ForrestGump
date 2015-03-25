#include "WorldManager.h"
#include "DAO/User.h"
#include "Definitions.h"
#include <iostream>

using namespace std;

WorldManager* WorldManager::m_pInstance = 0;

WorldManager* WorldManager::getInstance()
{	
	if (m_pInstance == 0)
	{
		m_pInstance = new WorldManager();
	}	
	return m_pInstance;
}

bool WorldManager::init()
{
	this->createDAO();
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

CollectableFactory* WorldManager::CollectableFactoryLayer()
{
	return (CollectableFactory*)WorldManager::layerWithTag(TAG_SEGMENT_MANAGER);
}

Layer* WorldManager::layerWithTag(int tag)
{
	Scene* scene = Director::getInstance()->getRunningScene();
	if (scene->getTag() == TAG_GAME_SCENE) {
		Layer* layer = (Layer*)scene->getChildByTag(tag);
		return layer;
	}
	return NULL;
}

void WorldManager::createDAO()
{
	m_DataAccessObject = std::shared_ptr<IGameDAO>(new GameDAO());	
	if (!this->isXMLFileExist())
	{		
		m_DataAccessObject->create();	
		this->addUser("David");
	}

	m_DataAccessObjectMySQL = std::shared_ptr<IGameDAO>(new GameDAOMySQL());	
}

bool WorldManager::isXMLFileExist()
{
	std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
	filepath.append(XMLDOC);
	CCLOG("%s", filepath.c_str());
	FILE *fp = fopen(filepath.c_str(), "r");
	bool bRet = false;

	if (fp)
	{
		bRet = true;
		fclose(fp);
	}

	return bRet;
}

void WorldManager::addUser(std::string username)
{
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	User user;

	// Player
	user.setUsername(username.c_str());
	user.addScore("0", "Highscore");
	user.addScore("0", "Distance");
	user.addScore("0", "Coins");
	user.addScore("0", "Items");
	user.addScore("0", "Boosters");
	user.addScore("0", "Food");
	user.addScore("0", "EnemiesKilled");

	// World Manager
	user.addScore("0", "TimePlayed");
		
	users->push_back(user);
	m_DataAccessObject->update(users);
}

void WorldManager::updateDAO()
{
	// XML
	// Read DAO
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	
	
	// Update DB	
	users->at(0).getScores()->at(0).setText(std::to_string(m_pPlayer->getHighScore()).c_str());
	users->at(0).getScores()->at(1).setText(std::to_string(m_pPlayer->getDistance()).c_str());
	users->at(0).getScores()->at(2).setText(std::to_string(m_pPlayer->getCoins()).c_str());
	users->at(0).getScores()->at(3).setText(std::to_string(m_pPlayer->getItems()).c_str());
	users->at(0).getScores()->at(4).setText(std::to_string(m_pPlayer->getBoosters()).c_str());
	users->at(0).getScores()->at(5).setText(std::to_string(m_pPlayer->getFood()).c_str());
	users->at(0).getScores()->at(6).setText(std::to_string(m_pPlayer->getEnemiesKilled()).c_str());
	users->at(0).getScores()->at(7).setText(std::to_string(m_nTimePlayedSeconds).c_str());
	
	
	/*
	for (int i = 0; i < users->size(); i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}
	*/
	m_DataAccessObject->update(users);

	// Update Remote MySQL DB		
}

std::string WorldManager::getPlayerUsername()
{
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
	CCLOG("World Manager reset");
}

void WorldManager::cleanUp()
{		
	m_pPlayer = NULL;
	m_pFloorSprite = NULL;
	m_DataAccessObject = NULL; // shared pointer
	delete m_pInstance;
	m_pInstance = NULL;
}
