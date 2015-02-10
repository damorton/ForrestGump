
#ifndef COLLISION_H_
#define	COLLISION_H_

// includes 
#include "cocos2d.h"
#include "Maze.h"
#include "Player.h"
#include <vector>
#include <memory>

// forward declarations
class Enemy;

class CollisionManager
{
public:
	virtual bool init();
	static CollisionManager* getInstance();			
	bool checkCollisions();
	void cleanUp(); 	
	Player* getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getVectorOfEnemies(){ return m_vpEnemies; }; 
	
	void registerEnemyWithCollisionManager(std::shared_ptr<Enemy> obj);
	void registerPlayer(Player* player){ m_pPlayer = player; };
	void registerSegmentTile(cocos2d::Sprite* segmentTile){ m_vpSegmentTiles.push_back(segmentTile); };
protected:
	Player* m_pPlayer; 
	//cocos2d::TMXLayer* m_pSegment;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; 
	std::vector<cocos2d::Sprite*> m_vpSegmentTiles;
private:
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
};

#endif