
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
	bool checkCollisons();
	void cleanUp(); 
	Player* getPlayer(){ return m_pPlayer; }; // player
	std::vector<std::shared_ptr<Enemy>> getVectorOfEnemies(){ return m_vpEnemies; }; // vector of enemies	
	void registerEnemyWithCollisionManager(std::shared_ptr<Enemy> obj);
	void registerPlayer(Player* player){ m_pPlayer = player; };
	void registerSegment(cocos2d::TMXLayer* layer);
private:
	static CollisionManager* m_Instance; 
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
protected:
	Player* m_pPlayer; // player 
	cocos2d::TMXLayer* m_pMazeLayer;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; // vector of GameObject pointers	
};

#endif