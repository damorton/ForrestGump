#ifndef COLLECTABLE_FACTORY
#define	COLLECTABLE_FACTORY

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class CollectableFactory : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual ~CollectableFactory(){ this->cleanup(); };
	void cleanup();
	bool addPhysicsEdgeBox();
	bool addPhysicsToTiles(TMXLayer* layer);	
	bool addItemsToActiveVector(TMXLayer* layer);
	bool addTMXTileMap(const std::string& filename);
	void setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	void removeLayer(Node* sender, void* layer);
	bool spawnSprites();
	//void resetSprite(Node* sender, void* tileSprite);		
	bool isSpawned(){ return m_bIsSpawned; };
	void update();	
	bool initTilePositions(TMXLayer* layer, std::string name);
	//void addSpriteBehaviour(Sprite* tileSprite);	
	void moveSprites();
	void resetItem(Sprite* item);
	CREATE_FUNC(CollectableFactory);
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pCoinLayer;
	TMXLayer* m_pItemLayer;
	TMXLayer* m_pBoosterLayer;
	TMXLayer* m_pFoodLayer;
	bool m_bIsSpawned;
	std::vector<Sprite*> m_vpActiveItems;
	int m_nNumberOfActiveItems;
};

#endif