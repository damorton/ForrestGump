#include "WorldManager.h"

WorldManager* WorldManager::m_Instance = 0;

WorldManager* WorldManager::getInstance()
{	
	if (m_Instance == 0)
	{
		m_Instance = new WorldManager();		
	}
	return m_Instance;
}


bool WorldManager::init()
{	
	m_sVisibleSize = Director::getInstance()->getVisibleSize();
	m_vOrigin = Director::getInstance()->getVisibleOrigin();
	return true;
}

void WorldManager::cleanUp()
{	
	delete m_Instance;
	m_Instance = NULL;
	m_pPlayer = NULL;
	m_pEnemy = NULL;
}

void WorldManager::scaleSpriteToFullScreenSize(Sprite* sprite)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	sprite->setScaleX(visibleSize.width / sprite->getContentSize().width);
	sprite->setScaleY(visibleSize.height / sprite->getContentSize().height);
}

