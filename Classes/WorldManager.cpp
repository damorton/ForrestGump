#include "WorldManager.h"
#include "DAO/User.h"
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

bool WorldManager::init()
{				
	this->createDAO();
	this->addUser("David");
	return true;
}

void WorldManager::createDAO()
{
	m_DataAccessObject = std::shared_ptr<IGameDAO>(new GameDAO());	
	//m_DataAccessObject->create();
	
	/*
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	for (int i = 0; i < users->size(); i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}
	*/	
}

void WorldManager::addUser(std::string username)
{
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	User user;
	user.setUsername(username.c_str());
	user.addScore("0");	// distance
	user.addScore("0");	// coins
	user.addScore("0");	// items
	user.addScore("0");	// boosters
	user.addScore("0");	// food
	users->push_back(user);
	m_DataAccessObject->update(users);
}

std::string WorldManager::getPlayerDistanceScore()
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

void WorldManager::setPlayerDistanceScore(std::string distanceScore)
{
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();
	users->at(0).getScores()->at(0).setText(distanceScore.c_str());
	m_DataAccessObject->update(users);
}

void WorldManager::cleanUp()
{		
	// auto release objects
	m_pFloorSprite = NULL;
	m_pPlayer = NULL;	

	// members of WorldManager
	
}
