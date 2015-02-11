#include "Maze.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"

bool Maze::init()
{	
	if (!Layer::init())
	{
		return false;
	}
	
	//this->addTMXTileMap("maps/CoinSegmentA.tmx");
	//this->addPhysicsToTiles("segment");
	//this->setPosition(Vec2(VISIBLE_SIZE_WIDTH, Director::getInstance()->getVisibleOrigin().y));	
	
	return true;
}

TMXTiledMap* Maze::spawnSegment()
{
	auto map = TMXTiledMap::create("maps/CoinSegmentA.tmx");
	map->setPosition(Vec2(VISIBLE_SIZE_WIDTH, Director::getInstance()->getVisibleOrigin().y));
	//auto layer = map->getLayer("segment");
	auto removeSegment = CallFunc::create(this, callfunc_selector(Maze::removeSegment));
	auto segmentBehaviour = Sequence::create(
		MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 2, 0)),
		removeSegment,
		RemoveSelf::create(),
		NULL);
	//this->runAction(segmentBehaviour);
	map->runAction(segmentBehaviour);
	m_bIsSpawned = true;
	CollisionManager::getInstance()->registerSegment(this);
	return map;
}


void Maze::removeSegment()
{ 
	m_MazeTileMap->removeFromParentAndCleanup(true);
	m_bIsSpawned = false; 	
}

bool Maze::addTMXTileMap(const std::string& filename)
{
	m_MazeTileMap = TMXTiledMap::create(filename);	
	return true;
}

bool Maze::rotateMaze(float duration, float angle)
{	
	auto rotate = RotateBy::create(duration, angle);
	this->runAction(RepeatForever::create(rotate));
	return true;
}

bool Maze::addPhysicsEdgeBox()
{
	auto mazeEdge = PhysicsBody::createEdgeBox(m_MazeTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	m_MazeTileMap->setPhysicsBody(mazeEdge);
	return true;
}

bool Maze::addPhysicsToTiles(const std::string& layername)
{
	m_pTileMapLayer = m_MazeTileMap->getLayer(layername);
	Size layerSize = m_pTileMapLayer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = m_pTileMapLayer->tileAt(Vec2(i, j));
			if (tileSprite)
			{				
				
				tileSprite->setPhysicsBody(PhysicsBody::createBox(Size(tileSprite->getContentSize().width, tileSprite->getContentSize().height)));
				tileSprite->getPhysicsBody()->setDynamic(false);
				tileSprite->getPhysicsBody()->setGravityEnable(false);
				//tileSprite->getPhysicsBody()->setCategoryBitmask(0x01);
				//tileSprite->getPhysicsBody()->setCollisionBitmask(0x02);
				//tileSprite->getPhysicsBody()->setContactTestBitmask(true);				
				tileSprite->setPosition(Vec2((tileSprite->getPosition().x + tileSprite->getContentSize().width / 2), (tileSprite->getPosition().y + tileSprite->getContentSize().height / 2)));						
			}
		}
	}
	return true;
}