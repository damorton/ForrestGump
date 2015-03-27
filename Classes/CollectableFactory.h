/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

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

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class CollectableFactory : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual void collectableFactoryCleanup();
	virtual ~CollectableFactory(){ this->collectableFactoryCleanup(); };

	/*
		TMX Tile Maps are added to the game scene. Each
		Tile map contains a number of layers.

		@param const std::string& filename TMX Tiled Map filepath
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
	
	void setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	bool isSpawned(){ return m_bIsSpawned; };
	void update();	
	
	void moveSprites();
	void resetItem(Sprite* item);
	CREATE_FUNC(CollectableFactory);
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pIntroCoinLayer;
	TMXLayer* m_pCoinLayer;
	TMXLayer* m_pItemLayer;
	TMXLayer* m_pBoosterLayer;
	TMXLayer* m_pFoodLayer;
	bool m_bIsSpawned;
	std::vector<Sprite*> m_vpItems;
	std::deque<Sprite*> m_vpActiveItems;
	int m_cActiveItems;
};

#endif