
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
	Maze* getSegment(){ return m_pSegment; };
		
	void registerPlayer(Player* player){ m_pPlayer = player; };
	void registerSegment(Maze* segment){ m_pSegment = segment; };
protected:
	Player* m_pPlayer; 	
	Maze* m_pSegment;
private:
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
};

#endif