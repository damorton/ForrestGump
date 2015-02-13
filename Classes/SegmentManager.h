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
	/*
		Initialize the SegmentManager layer
	*/
	virtual bool init();
	virtual ~SegmentManager(){};

	/*
		Add a TMX tilemap to the layer
	*/
	bool addTMXTileMap(const std::string& filename);

	/*
		Rotate the SegmentManager layer

		@param float speed of the rotation (default 30.0f)
		@param float angle to rotate the layer by (default 360)
	*/	
	bool rotateSegment(float duration = 30.0f, float angle = 360);

	/*
		Add physic edge box to the edge of the tilemap

		@return bool if physics edge box added
	*/
	bool addPhysicsEdgeBox();

	/*
		Add physics bodies to each of the tiles in the tilemap. The tilemap
		must be named in the Tiled software

		@param const std::string& filename of the layer
	*/
	bool addPhysicsToTiles(const std::string& layername);
		
	bool setTileMap(TMXTiledMap* tilemap){ m_pTileMap = tilemap; };		
	TMXLayer* getSegmentLayer(){ return m_Segment.layer; };
	bool spawnSegment(); 
	bool isSpawned(){ return m_bIsSpawned; };	
	void removeSegment();
	void update();
	void initSegment();

	/*
		Initialize the parent node
	*/
	CREATE_FUNC(SegmentManager);

private:
	TMXTiledMap* m_pTileMap;
	TMXLayer* m_pSegment;
	Segment m_Segment;
	bool m_bIsSpawned;
	int m_iSpawnSegmentTimer;
};

#endif