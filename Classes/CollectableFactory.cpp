#include "CollectableFactory.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"

bool CollectableFactory::init()
{	
	if (!Layer::init())
	{
		return false;
	}			
	m_iSpawnSegmentTimer = 0;
	this->addTMXTileMap("maps/SpawnManagerMap.tmx");
	

	m_pCoinLayer = m_pTileMap->getLayer("coins");	
	this->initTilePositions(m_pCoinLayer);

	m_pItemLayer = m_pTileMap->getLayer("items");
	this->initTilePositions(m_pItemLayer);

	m_pBoosterLayer = m_pTileMap->getLayer("boosters");
	this->initTilePositions(m_pBoosterLayer);

	m_pFoodLayer = m_pTileMap->getLayer("food");
	this->initTilePositions(m_pFoodLayer);

	CollisionManager::getInstance()->addLayer(m_pCoinLayer);
	CollisionManager::getInstance()->addLayer(m_pItemLayer);
	CollisionManager::getInstance()->addLayer(m_pBoosterLayer);
	CollisionManager::getInstance()->addLayer(m_pFoodLayer);
	
	srand(time(NULL));
	m_bIsSpawned = false;
	this->spawnSprites();	
	return true;
}

bool CollectableFactory::initTilePositions(TMXLayer* layer)
{
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{
				tileSprite->setPosition(Vec2(SCREEN_ORIGIN.x + tileSprite->getPositionX() + VISIBLE_SIZE_WIDTH, SCREEN_ORIGIN.y + tileSprite->getPositionY()));
			}
		}
	}	
	return true;
}

bool CollectableFactory::spawnSprites()
{		
	int randomnumber;
	int numberOfLayers = CollisionManager::getInstance()->getLayers().size();
	randomnumber = (rand() % numberOfLayers);

	switch (randomnumber)
	{
	case 0:
		this->addTileBehaviour(m_pCoinLayer, "coin");
		break;
	case 1:
		this->addTileBehaviour(m_pItemLayer, "item");		
		break;		
	case 2:
		this->addTileBehaviour(m_pBoosterLayer, "booster");
		break;
	case 3:
		this->addTileBehaviour(m_pFoodLayer, "food");
		break;
	default:
		CCLOG("segment spawn random number unknown");
	}	
	return true;
}

bool CollectableFactory::addTileBehaviour(TMXLayer* layer, std::string name)
{
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{
				tileSprite->setName(name);
				this->addSpriteBehaviour(tileSprite);				
			}
		}
	}	
	m_bIsSpawned = true;
	return true;
}

void CollectableFactory::addSpriteBehaviour(Sprite* tileSprite)
{
	if (tileSprite != NULL)
	{
		auto reset = CCCallFuncND::create(this, callfuncND_selector(CollectableFactory::resetSprite), (void*)tileSprite);
		auto tileSpriteBehaviour = Sequence::create(
			MoveBy::create(WORLD_MOVEMENT_SPEED, Point(-(VISIBLE_SIZE_WIDTH * 2), 0)),
			reset,
			NULL);
		tileSprite->runAction(tileSpriteBehaviour);
	}
}

bool CollectableFactory::addPhysicsToTiles(TMXLayer* layer)
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
			}
		}
	}
	return true;
}

void CollectableFactory::resetSprite(Node* sender, void* tileSprite)
{
	if (tileSprite != NULL)
	{
		Sprite* tile = static_cast<Sprite*>(tileSprite);
		tile->stopAllActions();				
		tile->setPosition(Vec2(tile->getPositionX() + (VISIBLE_SIZE_WIDTH * 2), tile->getPositionY()));
		tile->setVisible(true);		
		m_bIsSpawned = false;
	}	
}

void CollectableFactory::deleteTilemap(Node* sender, void* tilemap)
{ 		
	if (tilemap != NULL)
	{
		TMXTiledMap* tMap = static_cast<TMXTiledMap*>(tilemap);
		tMap->removeFromParentAndCleanup(true);
	}
}

void CollectableFactory::removeLayer(Node* sender, void* layer)
{
	if (!CollisionManager::getInstance()->getLayers().empty())
	{
		CollisionManager::getInstance()->removeLayer();
	}
}

bool CollectableFactory::addTMXTileMap(const std::string& filename)
{	
	m_pTileMap = TMXTiledMap::create(filename);
	m_pTileMap->setPosition(SCREEN_ORIGIN);
	this->addChild(m_pTileMap);
	return true;
}

bool CollectableFactory::rotateSegment(float duration, float angle)
{	
	auto rotate = RotateBy::create(duration, angle);
	m_pTileMap->runAction(RepeatForever::create(rotate));
	return true;
}

bool CollectableFactory::addPhysicsEdgeBox()
{
	auto CollectableFactoryEdge = PhysicsBody::createEdgeBox(m_pTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	m_pTileMap->setPhysicsBody(CollectableFactoryEdge);
	return true;
}

void CollectableFactory::update()
{	
	if (!m_bIsSpawned)
	{
		this->spawnSprites();
	}
}

void CollectableFactory::cleanup()
{
	m_pTileMap = NULL;
	m_pCoinLayer = NULL;
	m_pItemLayer = NULL;
	m_pBoosterLayer = NULL;
	m_pFoodLayer = NULL;
	m_bIsSpawned = false;
	m_iSpawnSegmentTimer = 0;
}