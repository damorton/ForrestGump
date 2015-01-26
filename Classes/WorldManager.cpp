#include "WorldManager.h"

// implementation
WorldManager* WorldManager::m_Instance = 0;

WorldManager* WorldManager::getInstance()
{
	// if the pointer is null set it to an instance 
	// of the WorldManager
	if (m_Instance == 0)
		m_Instance = new WorldManager();
	return m_Instance;
}


bool WorldManager::init()
{	
	return true;
}

void WorldManager::cleanUp()
{	
	delete m_Instance;
	m_Instance = NULL;
}

