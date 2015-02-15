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
	m_bIsSpawned = false;
	m_iSpawnSegmentTimer = 0;
	m_pTileMap = NULL;
	CCLOG("Segment Manager initialized");
	return true;
}

bool SegmentManager::spawnSegment()
{	
	m_pTileMap = TMXTiledMap::create("maps/CoinSegmentA.tmx");
	m_pTileMap->setPosition(SEGMENT_START_POS);
	this->addChild(m_pTileMap);	
	
	auto segment = m_pTileMap->getLayer("segment");
	this->addPhysicsToTiles(segment);
	
	auto removeSegment = CCCallFuncND::create(this,	callfuncND_selector(SegmentManager::deleteTilemap),	(void*)m_pTileMap);
	auto removeLayerFromCollisionManager = CCCallFuncND::create(this, callfuncND_selector(SegmentManager::removeFromCollisionManager), (void*)segment);
	auto segmentBehaviour = Sequence::create(
		MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 2, 0)),		
		RemoveSelf::create(),
		removeLayerFromCollisionManager,
		removeSegment,
		NULL);
	
	segment->runAction(segmentBehaviour);
	CollisionManager::getInstance()->registerSegment(segment);
	m_bIsSpawned = true;
	return true;
}

void SegmentManager::deleteTilemap(Node* sender, void* tilemap)
{ 		
	if (tilemap != NULL)
	{
		TMXTiledMap* tMap = static_cast<TMXTiledMap*>(tilemap);
		tMap->removeFromParentAndCleanup(true);
		CCLOG("Segment deleted");
	}
	m_bIsSpawned = false;
}

void SegmentManager::removeFromCollisionManager(Node* sender, void* layer)
{	
	CCLOG("Number of layers in collision manager before removal: %d", CollisionManager::getInstance()->getTMXLayerVector().size());
	if (layer != NULL)
	{
		TMXLayer* segmentLayer = static_cast<TMXLayer*>(layer);
		CCLOG("Removing layer %s from collision manager", segmentLayer->getLayerName());
		if (CollisionManager::getInstance()->getTMXLayerVector().front() != NULL)		
		{
			CollisionManager::getInstance()->getTMXLayerVector().pop_front();
			CCLOG("Layer deleted from the front of the layer queue in collision manager");
		}				
	}
	CCLOG("Number of layers in collision manager after removal: %d", CollisionManager::getInstance()->getTMXLayerVector().size());
}

bool SegmentManager::addTMXTileMap(const std::string& filename)
{	
	m_pTileMap = TMXTiledMap::create(filename);	
	
	return true;
}

bool SegmentManager::rotateSegment(float duration, float angle)
{	
	auto rotate = RotateBy::create(duration, angle);
	m_pTileMap->runAction(RepeatForever::create(rotate));
	return true;
}

bool SegmentManager::addPhysicsEdgeBox()
{
	auto SegmentManagerEdge = PhysicsBody::createEdgeBox(m_pTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	m_pTileMap->setPhysicsBody(SegmentManagerEdge);
	return true;
}

bool SegmentManager::addPhysicsToTiles(TMXLayer* layer)
{
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{		
				tileSprite->setPhysicsBody(PhysicsBody::createBox(Size(tileSprite->getContentSize().width, tileSprite->getContentSize().height)));
				tileSprite->getPhysicsBody()->setDynamic(true);
				tileSprite->getPhysicsBody()->setGravityEnable(false);				
				tileSprite->setPosition(Vec2((tileSprite->getPosition().x + tileSprite->getContentSize().width / 2), (tileSprite->getPosition().y + tileSprite->getContentSize().height / 2)));						
			}
		}
	}
	return true;
}

void SegmentManager::update()
{	
	m_iSpawnSegmentTimer++;
	if (m_iSpawnSegmentTimer > SEGMENT_SPAWN_TIME)
	{
		CCLOG("Spawn segment");		
		this->spawnSegment();
		m_iSpawnSegmentTimer = 0;
	}
}