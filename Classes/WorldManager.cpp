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
}

bool WorldManager::isXMLFileExist()
{
	std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
	filepath.append(XMLDOC);
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
	user.setUsername(username.c_str());
	user.addScore("0");	// distance	
	users->push_back(user);
	m_DataAccessObject->update(users);
}

std::string WorldManager::getPlayerHighscore()
{
	std::string playerDistance;
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	playerDistance = users->at(0).getScores()->at(0).getText().c_str();
	return playerDistance;
}

std::string WorldManager::getPlayerUsername()
{
	std::string playerUsername;
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	playerUsername = users->at(0).getUsername()->getText().c_str();
	return playerUsername;
}

void WorldManager::setPlayerHighscore(std::string highscore)
{
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	users->at(0).getScores()->at(0).setText(highscore.c_str());
	m_DataAccessObject->update(users);
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
