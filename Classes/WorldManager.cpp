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
