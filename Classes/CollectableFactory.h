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
	bool rotateSegment(float duration = 30.0f, float angle = 360);
	bool addPhysicsEdgeBox();
	bool addPhysicsToTiles(TMXLayer* layer);	
	bool addTileBehaviour(TMXLayer* layer, std::string name);
	bool addTMXTileMap(const std::string& filename);
	void setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	void deleteTilemap(Node* sender, void* tilemap);
	void removeLayer(Node* sender, void* layer);
	bool spawnSprites();
	void resetSprite(Node* sender, void* tileSprite);		
	bool isSpawned(){ return m_bIsSpawned; };
	void update();	
	bool initTilePositions(TMXLayer* layer);
	void addSpriteBehaviour(Sprite* tileSprite);	
	CREATE_FUNC(CollectableFactory);
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pCoinLayer;
	TMXLayer* m_pItemLayer;
	TMXLayer* m_pBoosterLayer;
	TMXLayer* m_pFoodLayer;
	bool m_bIsSpawned;
	int m_iSpawnSegmentTimer;	
};

#endif