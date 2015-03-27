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
#ifndef COLLECTABLE_FACTORY
#define	COLLECTABLE_FACTORY

// Includes
#include <iostream>
#include "Definitions.h"

class WorldManager;
class CollisionManager;

class CollectableFactory : public cocos2d::Layer
{
public:			
	virtual bool init(); // Initialize the collectable factory
	virtual void collectableFactoryCleanup();
	virtual ~CollectableFactory(){ this->collectableFactoryCleanup(); };

	/*
		TMX Tile Maps are added to the game scene. Each
		Tile map contains a number of layers.

		@param const std::string& filename TMX Tiled Map filepath
		@return bool true if successful
	*/
	bool addTMXTileMap(const std::string& filename);

	/*
		Adds tmx layer containing sprites to the game. 

		@param std::string layerName, name of the layer created in Tiled software
	*/
	void addItemLayer(std::string layerName);	

	/*
		Set each sprite in the tile layer to a starting poistion
		outside of the screen

		@param TMXLayer* layer, the layer containing the collectable sprites
		@param std::string name, the name given to each collectable sprites e.g coins, items, boosters.
		@return bool true if successful
	*/
	bool initTilePositions(TMXLayer* layer, std::string name);

	/*
		When the active vector of collectables is empty, spawn a new layer of 
		items

		@return bool true if successful
	*/
	bool spawnSprites();

	/*
		Set up the collectable sprites, add them to the active vector and
		register each with the collision manager

		@param std::string name of the item to be activated
		@return true if successful
	*/
	bool activateItems(std::string name);

	// Check if a layer of items is currently spawned
	bool isSpawned(){ return m_bIsSpawned; };

	/*
		Update controls all currently active items movements and is called
		from the main game loop. It calls the move function and also checks
		for spawn status
	*/
	void update();	
	
	// Move all sprites in the active items vector
	void moveSprites();

	// Reset the collectable sprite when it goes out of view
	void resetItem(Sprite* item);

	// Creates the Collectable Factory layer and adds it to the auto release pool	
	CREATE_FUNC(CollectableFactory);
private:

	// TMX Tiled Map
	TMXTiledMap* m_pTileMap;
	
	// Collectable items status and containers
	bool m_bIsSpawned;
	std::vector<Sprite*> m_vpItems;
	std::deque<Sprite*> m_vpActiveItems;
	int m_cActiveItems; // Used to clear the collision managers item vector

	WorldManager* m_pWorldManager;
	CollisionManager* m_pCollisionManager;
};

#endif