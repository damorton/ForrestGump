#include "Maze.h"

Maze::Maze(){}
Maze::~Maze(){}

Maze* Maze::createLayer(const std::string& filename)
{
	Maze* maze = new Maze();	
	maze->create(Color4B(0, 0, 255, 255), Color4B(0, 155, 255, 255));	
	maze->setContentSize(Size(1, 1));
	maze->setAnchorPoint(Vec2(0, 0));
	maze->setPosition(Vec2::ZERO);
	maze->addTMXTileMap(filename);
	return maze;
}

bool Maze::addTMXTileMap(const std::string& filename)
{
	m_MazeTileMap = TMXTiledMap::create(filename);
	m_MazeTileMap->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	this->addChild(m_MazeTileMap, 0, "TMXMaze");
	return true;
}

bool Maze::rotateMaze(float duration, float angle)
{	
	rotate = RotateBy::create(duration, angle);
	this->runAction(RepeatForever::create(rotate));
	return true;
}

bool Maze::addPhysicsEdgeBox()
{
	m_MazePhysicsEdge = PhysicsBody::createEdgeBox(m_MazeTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	m_MazeTileMap->setPhysicsBody(m_MazePhysicsEdge);
	return true;
}

bool Maze::addPhysicsToTilesOnLayer(const std::string& filename)
{
	m_TiledMazeLayer = m_MazeTileMap->getLayer(filename);
	Size layerSize = m_TiledMazeLayer->getLayerSize();
	for (int i = 0; i < layerSize.height; i++)
	{
		for (int j = 0; j < layerSize.width; j++)
		{
			auto tileSprite = m_TiledMazeLayer->tileAt(Vec2(i, j));
			if (tileSprite)
			{
				tileSprite->setPhysicsBody(PhysicsBody::createBox(Size(tileSprite->getContentSize().width, tileSprite->getContentSize().height)));
				tileSprite->getPhysicsBody()->setDynamic(false);
				tileSprite->setPosition(Vec2((tileSprite->getPosition().x + tileSprite->getContentSize().width / 2), (tileSprite->getPosition().y + tileSprite->getContentSize().height / 2)));
			}
		}
	}
	return true;
}