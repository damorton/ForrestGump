
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

/*	Singleton CollisionManager */
class CollisionManager
{
public:
	virtual bool init();
	static CollisionManager* getInstance();

	/*
		Register with the collision manager

		@param GameObject obj
		*/
	void registerEnemyWithCollisionManager(std::shared_ptr<Enemy> obj);

	/*
		Register the player object

		@param Sprite* player
		*/
	void registerPlayer(Player* player){ m_pPlayer = player; };

	/*
		TMX tile map layers
	*/
	void registerSegment(Maze* segment){ m_pSegmentLayer = segment; };
	
	/*
		Collision detection, check player against all other
		registered game objects

		@return bool true if collision, false if not
	*/
	bool checkCollisons();

	void cleanUp(); // delete CollisionManager

	// getters 
	Player* getPlayer(){ return m_pPlayer; }; // player
	std::vector<std::shared_ptr<Enemy>> getVectorOfEnemies(){ return m_vpEnemies; }; // vector of enemies
	
private:
	static CollisionManager* m_Instance; 
	CollisionManager(){ this->init(); }; // constructor
	~CollisionManager(){ this->cleanUp(); }; // deconstructor
	
	Player* m_pPlayer; // player 
	Maze* m_pSegmentLayer;
	std::vector<std::shared_ptr<Enemy>> m_vpEnemies; // vector of GameObject pointers	
};

#endif