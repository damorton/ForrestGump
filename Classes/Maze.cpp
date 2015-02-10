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
	this->setPosition(Vec2(VISIBLE_SIZE_WIDTH, Director::getInstance()->getVisibleOrigin().y));
	auto segmentBehaviour = Sequence::create(
		MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 2, 0)),
		RemoveSelf::create(),
		nullptr);
	this->runAction(segmentBehaviour);

	return true;
}

bool Maze::addTMXTileMap(const std::string& filename)
{
	m_MazeTileMap = TMXTiledMap::create(filename);	
	this->addChild(m_MazeTileMap, 0);
	this->addPhysicsToTiles("segment");
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
				tileSprite->getPhysicsBody()->setDynamic(true);
				tileSprite->getPhysicsBody()->setGravityEnable(false);
				tileSprite->getPhysicsBody()->setCategoryBitmask(0x01);
				tileSprite->getPhysicsBody()->setCollisionBitmask(0x02);
				tileSprite->getPhysicsBody()->setContactTestBitmask(true);
				tileSprite->setPosition(Vec2((tileSprite->getPosition().x + tileSprite->getContentSize().width / 2), (tileSprite->getPosition().y + tileSprite->getContentSize().height / 2)));		
				CollisionManager::getInstance()->registerSegmentTile(tileSprite);
			}
		}
	}
	return true;
}


Maze* Maze::spawnSegment()
{
	 return this;
}