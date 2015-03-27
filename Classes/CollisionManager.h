
/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	CollisionManager.h

	Description: Collision manager singleton handles all collisions that occur in game. Each game object
	is registered with the collision manager and checked for collisions against all other active objects in the game.
	The player is checked against each enemy in the active enemy vector, items in the active item vector and power ups.
	When a collision occurs the event triggers the game objects behaviours such as adding a coin to the score of
	being destroyed.
*/

#ifndef COLLISION_H_
#define	COLLISION_H_

// Includes
#include <vector>
#include <memory>
#include "Definitions.h"

// Forward declarations
class WorldManager;
class Player;
class Enemy;
class Shield;

class CollisionManager
{
public:
	virtual bool init();
	virtual void collisionManagerCleanup();
	static CollisionManager* getInstance();

	void checkCollisions();
	void checkCollisionsWithItems();
	void checkCollisionsWithEnemies();
	void resetCollisionManager();

	// function to check collisions with shields 
	void checkCollisionsWithShields();

	void setPlayer(Player* player){ m_pPlayer = player; };
	void addItem(Sprite* item){ m_vpItems.push_back(item); };
	void addEnemy(Enemy* enemy){ m_vpEnemies.push_back(enemy); };

	// function to add a shield to the vector
	void addShield(Shield* shield){ m_vpShields.push_back(shield); };

	Player* getPlayer(){ return m_pPlayer; };
	std::deque<Sprite*> getItemsVector(){ return m_vpItems; };
	std::vector<Enemy*> getEnemies(){ return m_vpEnemies; };

	// function to return a shield from the vector 
	std::vector<Shield*> getShields(){ return m_vpShields; };
	
	void removeItem(){ m_vpItems.pop_front(); };
	void removeEnemy(){ m_vpEnemies.pop_back(); };

	// function to the remove the shield from the vector
	void removeShield(){ m_vpShields.pop_back(); };
	
private:	
	static CollisionManager* m_Instance;
	CollisionManager(){ this->init(); }; 
	virtual ~CollisionManager(){ this->collisionManagerCleanup(); };
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;
	std::deque<Sprite*> m_vpItems;

	// a vector to hold the shields
	std::vector<Shield*> m_vpShields; 
	
	WorldManager* m_pWorldManager;

};

#endif