#ifndef SEGMENT_MANAGER_
#define	SEGMENT_MANAGER_

#include "cocos2d.h"

USING_NS_CC;

class SegmentManager : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual ~SegmentManager(){};	
	bool addTMXTileMap(const std::string& filename);	
	bool rotateSegment(float duration = 30.0f, float angle = 360);
	bool addPhysicsEdgeBox();
	bool addPhysicsToTiles(TMXLayer* layer);
	bool addTileBehaviour(TMXLayer* layer);
	bool setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	
	bool spawnSegment(); 
	bool isSpawned(){ return m_bIsSpawned; };	
	void deleteTilemap(Node* sender, void* tilemap);
	void removeLayer(Node* sender, void* layer);
	void update();
	
	CREATE_FUNC(SegmentManager);
private:
	TMXTiledMap* m_pTileMap;
	bool m_bIsSpawned;
	int m_iSpawnSegmentTimer;	
};

#endif