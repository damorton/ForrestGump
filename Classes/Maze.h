#ifndef MAZE_H_
#define	MAZE_H_

#include "cocos2d.h"

USING_NS_CC;

class Maze : public cocos2d::Layer
{
public:		
	/*
		Initialize the maze layer
	*/
	virtual bool init();

	/*
		Add a TMX tilemap to the layer
	*/
	bool addTMXTileMap(const std::string& filename);

	/*
		Rotate the maze layer

		@param float speed of the rotation (default 30.0f)
		@param float angle to rotate the layer by (default 360)
	*/	
	bool rotateMaze(float duration = 30.0f, float angle = 360);

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
	bool addPhysicsToTiles(const std::string& filename);
	
	/*
		Set TMX tilemap for the maze

		@param TMXTiledMap* tilemap 
	*/
	bool setTileMap(TMXTiledMap* tilemap){ m_MazeTileMap = tilemap; };

	/*
		Get the TMX tilemap for the maze

		@return TMXTiledMap* m_MazeTileMap
	*/
	TMXTiledMap* getTileMap(){ return m_MazeTileMap; };

	/*
		Initialize the parent node
	*/
	CREATE_FUNC(Maze);

private:
	TMXTiledMap* m_MazeTileMap;	
};

#endif