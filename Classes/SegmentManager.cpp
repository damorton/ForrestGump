#include "SegmentManager.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"

bool SegmentManager::init()
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

TMXTiledMap* SegmentManager::spawnSegment()
{
	auto m_SegmentManagerTileMap = TMXTiledMap::create("maps/CoinSegmentA.tmx");
	m_pTileMapLayer = m_SegmentManagerTileMap->getLayer("segment");
	m_SegmentManagerTileMap->setPosition(Vec2(VISIBLE_SIZE_WIDTH, Director::getInstance()->getVisibleOrigin().y));
	auto removeSegment = CallFunc::create(this, callfunc_selector(SegmentManager::removeSegment));
	auto segmentBehaviour = Sequence::create(
		MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 2, 0)),
		removeSegment,
		RemoveSelf::create(),
		NULL);
	//this->runAction(segmentBehaviour);
	m_SegmentManagerTileMap->runAction(segmentBehaviour);
	m_bIsSpawned = true;
	CollisionManager::getInstance()->registerSegment(this);
	return m_SegmentManagerTileMap;
}


void SegmentManager::removeSegment()
{ 
	m_SegmentManagerTileMap->removeFromParentAndCleanup(true);
	m_bIsSpawned = false; 	
}

bool SegmentManager::addTMXTileMap(const std::string& filename)
{
	m_SegmentManagerTileMap = TMXTiledMap::create(filename);	
	return true;
}

bool SegmentManager::rotateSegmentManager(float duration, float angle)
{	
	auto rotate = RotateBy::create(duration, angle);
	m_SegmentManagerTileMap->runAction(RepeatForever::create(rotate));
	return true;
}

bool SegmentManager::addPhysicsEdgeBox()
{
	auto SegmentManagerEdge = PhysicsBody::createEdgeBox(m_SegmentManagerTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	m_SegmentManagerTileMap->setPhysicsBody(SegmentManagerEdge);
	return true;
}

bool SegmentManager::addPhysicsToTiles(const std::string& layername)
{
	m_pTileMapLayer = m_SegmentManagerTileMap->getLayer(layername);
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