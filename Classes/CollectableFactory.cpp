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
	this->addTMXTileMap("maps/SpawnManagerMap.tmx");
	
	m_pCoinLayer = m_pTileMap->getLayer("coins");	
	this->initTilePositions(m_pCoinLayer, "coins");

	m_pItemLayer = m_pTileMap->getLayer("items");
	this->initTilePositions(m_pItemLayer, "items");

	m_pBoosterLayer = m_pTileMap->getLayer("boosters");
	this->initTilePositions(m_pBoosterLayer, "boosters");

	m_pFoodLayer = m_pTileMap->getLayer("food");
	this->initTilePositions(m_pFoodLayer, "food");	
	
	srand(time(NULL));
	m_nNumberOfActiveItems = 0;
	m_bIsSpawned = false;
	this->spawnSprites();	
	return true;
}

bool CollectableFactory::initTilePositions(TMXLayer* layer, std::string name)
{
	layer->setPosition(Vec2::ZERO);
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{
				tileSprite->setName(name);
				tileSprite->setPosition(Vec2(tileSprite->getPositionX() + VISIBLE_SIZE_WIDTH, tileSprite->getPositionY()));
				tileSprite->setVisible(false);
			}
		}
	}	
	CollisionManager::getInstance()->addLayer(layer);
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
		this->addItemsToActiveVector(m_pCoinLayer);
		break;
	case 1:
		this->addItemsToActiveVector(m_pItemLayer);
		break;		
	case 2:
		this->addItemsToActiveVector(m_pBoosterLayer);
		break;
	case 3:
		this->addItemsToActiveVector(m_pFoodLayer);
		break;
	default:
		CCLOG("segment spawn random number unknown");
	}	
	return true;
}

bool CollectableFactory::addItemsToActiveVector(TMXLayer* layer)
{
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = layer->tileAt(Vec2(i, j));
			if (tileSprite)
			{		
				tileSprite->setVisible(true);
				m_vpActiveItems.push_back(tileSprite);
				m_nNumberOfActiveItems++;
			}
		}
	}	
	m_bIsSpawned = true;
	return true;
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
				tileSprite->getPhysicsBody()->setGravityEnable(true);
			}
		}
	}
	return true;
}

void CollectableFactory::resetItem(Sprite* item)
{	
	if(item != NULL)
	{
		Sprite* tile = static_cast<Sprite*>(item);
		tile->setPosition(Vec2(tile->getPositionX() + (VISIBLE_SIZE_WIDTH * 2), tile->getPositionY()));
		tile->setVisible(false);	
		m_nNumberOfActiveItems--;
		if (m_nNumberOfActiveItems < 1)
		{
			m_vpActiveItems.clear();
			m_bIsSpawned = false;
		}
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
	this->addChild(m_pTileMap);
	return true;
}

bool CollectableFactory::addPhysicsEdgeBox()
{
	auto CollectableFactoryEdge = PhysicsBody::createEdgeBox(m_pTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	m_pTileMap->setPhysicsBody(CollectableFactoryEdge);
	return true;
}

void CollectableFactory::moveSprites()
{
	if (!m_vpActiveItems.empty())
	{
		for (std::vector<Sprite*>::size_type it = 0; it < m_vpActiveItems.size(); ++it)
		{
			auto item = m_vpActiveItems.at(it);
			if (item)
			{
				item->setPosition(Vec2(item->getPosition().x - WORLD_MOVEMENT_SPEED, item->getPosition().y));
				if (item->getPosition().x < -item->getContentSize().width / 2){
					this->resetItem(item);					
				}
			}
		}
	}
}

void CollectableFactory::cleanup()
{
	m_pTileMap = NULL;
	m_pCoinLayer = NULL;
	m_pItemLayer = NULL;
	m_pBoosterLayer = NULL;
	m_pFoodLayer = NULL;
}

void CollectableFactory::update()
{	
	if (!m_bIsSpawned)
	{
		this->spawnSprites();
	}
	this->moveSprites();
}
