
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
	
	Player* getPlayer(){ return m_pPlayer; };
	std::vector<std::shared_ptr<Enemy>> getVectorOfEnemies(){ return m_vpEnemies; }; 
	
	void registerEnemyWithCollisionManager(std::shared_ptr<Enemy> obj);
	void registerPlayer(Player* player){ m_pPlayer = player; };
	//void registerSegment(cocos2d::TMXLayer* segment);
protected:
	Player* m_pPlayer; 
	//cocos2d::TMXLayer* m_pSegment;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; 
private:
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
};

#endif