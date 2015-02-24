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
	return true;
}

void WorldManager::createDAO()
{
	m_DataAccessObject = std::shared_ptr<IGameDAO>(new GameDAO());
	std::shared_ptr<std::vector<User>> users = m_DataAccessObject->read();

	// remove comments to add to the game.xml file

	/*
	User john;
	john.setUsername("John");
	john.addScore("Distance 3890");
	john.addScore("Coins 7893");

	User tom;
	tom.setUsername("Tom");
	tom.addScore("Distance 456");
	tom.addScore("Coins 10");

	users->push_back(john);
	users->push_back(tom);
	*/

	for (int i = 0; i < users->size(); i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}

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
