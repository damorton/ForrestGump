#include "WorldManager.h"

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
	return (GameScene *)WorldManager::layerWithTag(TAG_GAME_LAYER);
}

HUD* WorldManager::hudLayer()
{
	return (HUD*)WorldManager::layerWithTag(TAG_HUD);
}

CCLayer* WorldManager::layerWithTag(int tag)
{
	CCScene* scene = CCDirector::sharedDirector()->getRunningScene();
	if (scene->getTag() == TAG_GAME_SCENE) {
		CCLayer *layer = (CCLayer *)scene->getChildByTag(tag);
		return layer;
	}
	return NULL;
}

bool WorldManager::init()
{		
	return true;
}

void WorldManager::cleanUp()
{	
	delete m_pInstance;
		
	m_pInstance = NULL;
	m_cSplashScene = NULL;
	m_pFloorSprite = NULL;
	m_pPlayer = NULL;	
}
