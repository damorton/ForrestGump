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

void SegmentManager::initSegment()
{	
}

bool SegmentManager::spawnSegment()
{	
	m_pTileMap = TMXTiledMap::create("maps/CoinSegmentA.tmx");
	m_pTileMap->setPosition(SEGMENT_START_POS);
	this->addChild(m_pTileMap);

	m_pSegment = m_pTileMap->getLayer("segment");
	
	auto removeSegment = CCCallFuncND::create(
		this,
		callfuncND_selector(SegmentManager::deleteTilemap),
		(void*)m_pTileMap);
	auto segmentBehaviour = Sequence::create(
		MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 2, 0)),		
		RemoveSelf::create(),
		deleteTilemap,
		NULL);
	
	m_pSegment->runAction(segmentBehaviour);
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

bool SegmentManager::addPhysicsToTiles(const std::string& layername)
{
	m_Segment.layer = m_pTileMap->getLayer(layername);
	Size layerSize = m_Segment.layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = m_Segment.layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{		
				tileSprite->setPhysicsBody(PhysicsBody::createBox(Size(tileSprite->getContentSize().width, tileSprite->getContentSize().height)));
				tileSprite->getPhysicsBody()->setDynamic(false);
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
	if (m_iSpawnSegmentTimer > 100)
	{
		CCLOG("Spawn segment");		
		this->spawnSegment();
		m_iSpawnSegmentTimer = 0;
	}
}