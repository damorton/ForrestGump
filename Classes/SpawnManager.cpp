#include "Enemy.h"
#include "WorldManager.h"
#include "SpawnManager.h"
#include "Definitions.h"

USING_NS_CC;

bool SpawnManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setPosition(Vec2(VISIBLE_SIZE_WIDTH, Director::getInstance()->getVisibleOrigin().y));
	
	return true;
}

void SpawnManager::update()
{

}



