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
	m_iSpawnSegmentTimer = 0;
	m_pTileMap = NULL;
	m_pTileMap = TMXTiledMap::create("maps/CoinSegmentA.tmx");
	m_pTileMap->setPosition(SEGMENT_START_POS);
	this->addChild(m_pTileMap);	
	m_pCoinLayer = m_pTileMap->getLayer("segment");		
	CollisionManager::getInstance()->addLayer(m_pCoinLayer);
	this->spawnSprites();	
	CCLOG("Segment Manager initialized");	
	return true;
}

bool SegmentManager::spawnSprites()
{
	//this->addPhysicsToTiles(m_pCoinLayer);
	this->addTileBehaviour(m_pCoinLayer);	
	return true;
}

void SegmentManager::addSpriteBehaviour(Sprite* tileSprite)
{
	if (tileSprite != NULL)
	{
		auto reset = CCCallFuncND::create(this, callfuncND_selector(SegmentManager::resetSprite), (void*)tileSprite);
		auto tileSpriteBehaviour = Sequence::create(
			MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 3, 0)),
			reset,
			NULL);
		tileSprite->runAction(tileSpriteBehaviour);
	}
}

void SegmentManager::resetSprite(Node* sender, void* tileSprite)
{
	if (tileSprite != NULL)
	{
		Sprite* tile = static_cast<Sprite*>(tileSprite);
		tile->stopAllActions();				
		tile->setPosition(Vec2(tile->getPositionX() + (VISIBLE_SIZE_WIDTH * 3), tile->getPositionY()));
		tile->setVisible(true);
		this->addSpriteBehaviour(tile);
		CCLOG("Tile reset");
	}	
}

bool SegmentManager::spawnSegment()
{	
	/*
	m_pTileMap = TMXTiledMap::create("maps/CoinSegmentA.tmx");
	m_pTileMap->setPosition(SEGMENT_START_POS);
	this->addChild(m_pTileMap);

	TMXLayer* segment = m_pTileMap->getLayer("segment");
	this->addPhysicsToTiles(segment);
	this->addTileBehaviour(segment);	
	auto removeSegment = CCCallFuncND::create(this,	callfuncND_selector(SegmentManager::deleteTilemap),	(void*)m_pTileMap);
	auto removeLayer = CCCallFuncND::create(this, callfuncND_selector(SegmentManager::removeLayer), (void*)segment);
	auto segmentBehaviour = Sequence::create(
		MoveBy::create(SEGMENT_MOVEMENT_SPEED * VISIBLE_SIZE_WIDTH, Point(-VISIBLE_SIZE_WIDTH * 3, 0)),
		RemoveSelf::create(),
		removeLayer,
		removeSegment,
		NULL);	
	segment->runAction(segmentBehaviour);		
	CollisionManager::getInstance()->addLayer(segment);
	m_bIsSpawned = true;
	*/
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

void SegmentManager::removeLayer(Node* sender, void* layer)
{
	if (!CollisionManager::getInstance()->getLayers().empty())
	{
		CollisionManager::getInstance()->removeLayer();
	}
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

bool SegmentManager::addTileBehaviour(TMXLayer* layer)
{	
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{			
				this->addSpriteBehaviour(tileSprite);
			}
		}
	}
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
	// spawn a new segment (TMXTileMap)
	m_iSpawnSegmentTimer++;
	if (m_iSpawnSegmentTimer > SEGMENT_SPAWN_TIME)
	{
		//CCLOG("Spawn segment");		
		//this->spawnSegment();
		
		m_iSpawnSegmentTimer = 0;
	}
}