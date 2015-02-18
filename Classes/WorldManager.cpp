#include "WorldManager.h"
#include <iostream>
#include "DAO/User.h"
#include "DAO/GameDAO.h"

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
	cout << "test" << endl;
		
	IGameDAO* dao = new GameDAO();
	std::shared_ptr<std::vector<User>> users = dao->read();
		
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
	*/

	for (int i = 0; i < 2; i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}

	dao->update(users);
	return true;
}

void WorldManager::cleanUp()
{		
	m_pFloorSprite = NULL;
	m_pPlayer = NULL;	
}
