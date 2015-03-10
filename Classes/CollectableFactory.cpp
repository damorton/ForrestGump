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
	this->addItemLayer("introCoins");
	this->addItemLayer("coins");
	this->addItemLayer("coinsA");
	this->addItemLayer("coinsB");
	this->addItemLayer("coinsC");
	this->addItemLayer("items");
	this->addItemLayer("boosters");
	this->addItemLayer("food");
	srand(time(NULL));
	m_bIsSpawned = false;	
	m_cActiveItems = 0;
	this->activateItems("introCoins");
	CCLOG("Collectable factory init");
	return true;
}

void CollectableFactory::addItemLayer(std::string layerName)
{
	auto layer = m_pTileMap->getLayer(layerName);
	this->initTilePositions(layer, layerName);
}

bool CollectableFactory::addTMXTileMap(const std::string& filename)
{
	m_pTileMap = TMXTiledMap::create(filename);
	this->addChild(m_pTileMap);
	return true;
}

bool CollectableFactory::initTilePositions(TMXLayer* layer, std::string name)
{	
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto item = layer->tileAt(Vec2(i, j));
			if (item)
			{
				item->setName(name);
				item->setPosition(Vec2(item->getPositionX() + VISIBLE_SIZE_WIDTH, SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height + item->getPositionY()));
				item->setVisible(true);
				m_vpItems.push_back(item);				
			}
		}
	}		
	return true;
}

bool CollectableFactory::spawnSprites()
{		
	int randomnumber;
	int numberOfLayers = 7;	
	randomnumber = (rand() % numberOfLayers);
		
	switch (randomnumber)
	{
	case 0:
		this->activateItems("coins");
		break;
	case 1:
		this->activateItems("coinsA");
		break;
	case 2:
		this->activateItems("coinsB");
		break;
	case 3:
		this->activateItems("coinsC");
		break;
	case 4:
		this->activateItems("items");
		break;
	case 5:
		this->activateItems("boosters");
		break;
	case 6:
		this->activateItems("food");
		break;
	default:
		CCLOG("segment spawn random number unknown");
	}	
	return true;
}

bool CollectableFactory::activateItems(std::string name)
{	
	if (!m_vpItems.empty())
	{
		for (auto &item : m_vpItems)
		{
			if (item)
			{
				if (item->getName() == name)
				{
					item->setVisible(true);
					m_vpActiveItems.push_back(item);
					m_cActiveItems++;
					CollisionManager::getInstance()->addItem(item);
				}
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
		tile->setPosition(Vec2(tile->getPositionX() + tile->getParent()->getContentSize().width*2 + VISIBLE_SIZE_WIDTH, tile->getPositionY()));
		tile->setVisible(false);
		m_cActiveItems--;
		CollisionManager::getInstance()->removeItem();
	}
	if (m_cActiveItems <= 0) m_vpActiveItems.clear();
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
				item->setPosition(Vec2(item->getPosition().x - WorldManager::getInstance()->getGameWorldSpeed(), item->getPosition().y));
				if (item->getPosition().x < -item->getParent()->getContentSize().width){
					this->resetItem(item);
				}
			}
		}		
	}	
}

void CollectableFactory::update()
{	
	if (m_vpActiveItems.empty())
	{
		this->spawnSprites();
	}
	this->moveSprites();
}

void CollectableFactory::collectableFactoryCleanup()
{
	m_pTileMap = NULL;
	m_pCoinLayer = NULL;
	m_pIntroCoinLayer = NULL;
	m_pItemLayer = NULL;
	m_pBoosterLayer = NULL;
	m_pFoodLayer = NULL;
	m_vpItems.clear();
	m_vpActiveItems.clear();	
	CCLOG("Collectable Factory cleanup");
}

