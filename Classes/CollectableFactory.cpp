/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	CollectableFactory.h

	Description: Collectable factory controls all collectable items by the player.
	The collectables are created, managed and updated in the Collectable factory.
	The Collectable factory imports TMXTileMaps and converts each tile on each layer into
	a game sprite and manages their behaviour. Tile sprites are moved, reset, updated and removed
	by the collectable factory.The TMX Tile Maps are created using the Tiled Map Editor software.
	http://www.mapeditor.org
*/
// Includes
#include "CollectableFactory.h"
#include "WorldManager.h"
#include "CollisionManager.h"

bool CollectableFactory::init()
{	
	// Calls the super class constructor and adds the layer to the auto release pool
	if (!Layer::init())
	{
		return false;
	}			
	m_pWorldManager = WorldManager::getInstance();
	m_pCollisionManager = CollisionManager::getInstance();

	// Initialise and parse the TMX Tiled Map and its layers
	this->addTMXTileMap("maps/SpawnManagerMap.tmx");	
	this->addItemLayer("introCoins");
	this->addItemLayer("coins");
	this->addItemLayer("coinsA");
	this->addItemLayer("coinsB");
	this->addItemLayer("coinsC");
	this->addItemLayer("items");
	this->addItemLayer("boosters");
	this->addItemLayer("food");

	// Seed the random number generator for the item layers
	srand(time(NULL));
	
	// Spawn status and active item vector size, used to empty the collision managers item vector
	m_bIsSpawned = false;	
	m_cActiveItems = 0;

	// Spawn the intro pattern of coins
	this->activateItems("introCoins");
	//CCLOG("Collectable factory initialised");
	return true;
}

void CollectableFactory::addItemLayer(std::string layerName)
{
	// Get item layer by its name in the Tiled map
	auto layer = m_pTileMap->getLayer(layerName);
	this->initTilePositions(layer, layerName);
}

bool CollectableFactory::addTMXTileMap(const std::string& filename)
{	
	// Create the TMXTiledMap object using the filename parameter add it to the Collectable Factory	
	m_pTileMap = TMXTiledMap::create(filename);		
	this->addChild(m_pTileMap);
	return true;
}

bool CollectableFactory::initTilePositions(TMXLayer* layer, std::string name)
{		
	// Loop through each tile in the tilemap and the set the sprites poisition in game
	Size layerSize = layer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			// Only set the positions, names and visibility of sprites in the tilemap
			auto item = layer->tileAt(Vec2(i, j));
			if (item)
			{				
				item->setName(name);
				item->setPosition(Vec2(item->getPositionX() + VISIBLE_SIZE_WIDTH, SCREEN_ORIGIN.y + m_pWorldManager->getFloorSprite()->getContentSize().height + item->getPositionY()));
				item->setVisible(true);

				// Register the item with the collectable factory
				m_vpItems.push_back(item);				
			}
		}
	}		
	return true;
}

bool CollectableFactory::spawnSprites()
{		
	// Sprites are spawned randomly and called by the name given to them when they were initialised
	int randomnumber;
	int numberOfLayers = 7;	
	randomnumber = (rand() % numberOfLayers);
		
	// Switch statment will choose a layer based on the random number
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
	// Loop through the vector of items and initilise items identified
	// by the name param
	if (!m_vpItems.empty())
	{
		for (auto &item : m_vpItems)
		{
			if (item)
			{
				if (item->getName() == name)
				{
					// Items must be visible and in the active vector in order
					// to be collected by the player
					item->setVisible(true);
					m_vpActiveItems.push_back(item);
					m_cActiveItems++;
					m_pCollisionManager->addItem(item);
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
		// Static cast the shared pointer to the item sprite 
		Sprite* tile = static_cast<Sprite*>(item);		

		// Reset the sprites position outside the screen view to the right and decrement the active vector count
		tile->setPosition(Vec2(tile->getPositionX() + tile->getParent()->getContentSize().width*2 + VISIBLE_SIZE_WIDTH, tile->getPositionY()));
		tile->setVisible(false);
		m_cActiveItems--;

		// Remove the sprite from the collision manager
		m_pCollisionManager->removeItem();
	}

	// If the active item count is zero, clear the vector to be safe
	if (m_cActiveItems <= 0) m_vpActiveItems.clear();
}

void CollectableFactory::moveSprites()
{	
	// Loop through the active items vector and move each sprite from right to left accross the screen
	if (!m_vpActiveItems.empty())
	{		
		for (std::vector<Sprite*>::size_type it = 0; it < m_vpActiveItems.size(); ++it)
		{
			auto item = m_vpActiveItems.at(it);
			if (item)
			{
				item->setPosition(Vec2(item->getPosition().x - m_pWorldManager->getGameWorldSpeed(), item->getPosition().y));
				if (item->getPosition().x < -item->getParent()->getContentSize().width){
					this->resetItem(item);
				}
			}
		}		
	}	
}

void CollectableFactory::update()
{	
	// Collectable factories update method is called from the main game loop
	// Spawn a new set of items when there is not currently a set active
	if (m_vpActiveItems.empty())
	{
		this->spawnSprites();
	}
	
	// Move each item across the screen
	this->moveSprites();
}

void CollectableFactory::collectableFactoryCleanup()
{
	// Clean up the Collectable Factory
	m_pTileMap = NULL;	
	m_pWorldManager = NULL;
	m_pCollisionManager = NULL;
	m_vpItems.clear();
	m_vpActiveItems.clear();	
	//CCLOG("Collectable Factory cleanup");
}

