#ifndef SEGMENT_MANAGER_
#define	SEGMENT_MANAGER_

#include "cocos2d.h"

USING_NS_CC;

class SegmentManager : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual ~SegmentManager(){};	
	
	bool rotateSegment(float duration = 30.0f, float angle = 360);
	bool addPhysicsEdgeBox();
	bool addPhysicsToTiles(TMXLayer* layer);

	/*
		Add tile behaviour
		@param TMXLayer* layer of the tilemap with tile sprites		
		@return bool true if successful
	*/
	bool addTileBehaviour(TMXLayer* layer);
	
	bool addTMXTileMap(const std::string& filename);
	bool setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	void deleteTilemap(Node* sender, void* tilemap);

	void removeLayer(Node* sender, void* layer);

	bool spawnSprites();
	void resetSprite(Node* sender, void* tileSprite);
		
	bool isSpawned(){ return m_bIsSpawned; };
	void update();
	
	/*
		Initialize tile positions
		@param TMXLayer* layer of the tilemap with tile sprites
		@return bool true if successful
	*/
	bool SegmentManager::initTilePositions(TMXLayer* layer);
	void addSpriteBehaviour(Sprite* tileSprite);
	
	CREATE_FUNC(SegmentManager);
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