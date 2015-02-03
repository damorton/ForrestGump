#ifndef MAZE_H_
#define	MAZE_H_

#include "cocos2d.h"

USING_NS_CC;

class Maze : public cocos2d::LayerGradient
{
public:
	Maze();
	~Maze();

	/*
		Create a maze layer using .tmx tilemap

		@param const std::string& filename of the .tmx tilemap
		@return Maze* maze
	*/
	static Maze* createLayer(const std::string& filename);
	
	bool addTMXTileMap(const std::string& filename);

	/*
		Rotate the maze layer

		@param float speed of the rotation (default 30.0f)
		@param float angle to rotate the layer by (default 360)
	*/	
	bool rotateMaze(float duration = 30.0f, float angle = 360);

	bool addPhysicsEdgeBox();
	bool addPhysicsToTilesOnLayer(const std::string& filename);
	
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

private:
	TMXTiledMap* m_MazeTileMap;
	PhysicsBody* m_MazePhysicsEdge;
	RotateBy* rotate;
	TMXLayer* m_TiledMazeLayer;
};

#endif