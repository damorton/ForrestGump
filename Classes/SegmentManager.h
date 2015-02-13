#ifndef SEGMENT_MANAGER_
#define	SEGMENT_MANAGER_

#include "cocos2d.h"

USING_NS_CC;

struct Segment{
	TMXLayer* layer = NULL;
	bool isInit = false;
	bool isSpawned = false;
};

class SegmentManager : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual ~SegmentManager(){};	
	bool addTMXTileMap(const std::string& filename);	
	bool rotateSegment(float duration = 30.0f, float angle = 360);
	bool addPhysicsEdgeBox();
	bool addPhysicsToTiles(const std::string& layername);		
	bool setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	TMXLayer* getSegmentLayer(){ return m_Segment.layer; };
	bool spawnSegment(); 
	bool isSpawned(){ return m_bIsSpawned; };	
	void deleteTilemap(Node* sender, void* data);
	void update();
	void initSegment();
	CREATE_FUNC(SegmentManager);
private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pSegment;
	Segment m_Segment;
	bool m_bIsSpawned;
	int m_iSpawnSegmentTimer;
};

#endif