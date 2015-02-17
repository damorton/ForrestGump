#include "WorldManager.h"
#include <iostream>
#include "DAO/Node.h"
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

	/*std::shared_ptr<Node> node = Node::create();
	cout << "Node X: " << node->getX() << endl;
	cout << "Node Y: " << node->getY() << endl;


	std::shared_ptr<Node> node2 = Node::create(12, 2);
	cout << "Node X: " << node2->getX() << endl;
	cout << "Node Y: " << node2->getY() << endl;

	std::shared_ptr<Node> node3 = Node::create(true);
	cout << "Node X: " << node3->getX() << endl;
	cout << "Node Y: " << node3->getY() << endl;
	std::shared_ptr<Node> node4 = Node::create(12, 2, true);
	cout << "Node X: " << node4->getX() << endl;
	cout << "Node Y: " << node4->getY() << endl;
	*/
	IGameDAO* dao = new GameDAO();
	std::shared_ptr<std::vector<User>> users = dao->read();

	//todo:fix tinyxml errors. UserDefault already uses tinyxml in cocos2d::UserDefault
	// check the GameDAO.cpp for a comment starting the user default search

	/*
	User user;
	user.setUsername("John");
	user.addScore("Distance 3890");
	user.addScore("Coins 7893");

	users->push_back(user);
	*/

	for (int i = 0; i < 2; i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText());
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
