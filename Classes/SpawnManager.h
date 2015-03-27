/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	SpawnManager.h

	Description: The SpawnManager controls all enemy spawns within the game.
	It contains a reference to the enemy object. We create the enemies within
	the manager and we control there movements and allocation of resources.
*/

#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

// Includes
#include <iostream>
#include "Definitions.h"

// Forward Declarations
class Player;
class Enemy;
class Shield;
class WorldManager;
class CollisionManager;

class SpawnManager : public cocos2d::Layer
{
public:	
	// Init
	bool init();

	// Deconstructor
	virtual ~SpawnManager(){ this->spawnManagerCleanup(); };
	
	// Clean
	virtual void spawnManagerCleanup();
	// Update
	void update();

	// Adds enemy to vector and sets bool to spawned
	bool spawnEnemy();

	// Generates a random y value for enemies
	int getRandomHeight();

	// generates a random x value for enemies
	int getRandomXPos();

	// Gets the current number of spawned enemies
	int getEnemyCount();

	/* 
		Adds enemy to active vector and sets enemy to visible

		@param enemy object
	*/
	bool addEnemyToActiveVector(Enemy* enemy);

	// Defines the enemy movement behaviour
	void moveSprites();

	// Resets the enemey positon to a random x and y
	void resetEnemy(Enemy* enemy);

	//	Creates all enemies within the game
	void createEnemies();

	/* 
		Gets the resource filepath and creates an enemy, positions are also set here

		@param filepath 
		@param enemy name
		@param gravity bool 
		@param rotation bool
	*/
	void createEnemy(std::string filename, std::string name, bool gravity, bool rotate);
	
	// Pauses all enemies and their actions
	void pauseGame();

	// Resumes all enemies and their actions
	void resumeGame();

	// Spawns shield
	bool spawnShield();
	
	// Function to create shields by passing in the filename
	void createShields();

	// Function to take in the arguments to create the shield and add it to spawn manager
	void createShield(std::string filename, bool gravity, bool rotate);

	/* 
		Function to add shield to the active vector

		@param filename
		@param gravity
		@param rotate
	*/
	bool addShieldToActiveVector(Shield* shield);

	/*	
		Function to move the shields

		@param Shield object

		@return bool
	*/
	void moveShields();

	// Function to reset the shield 
	void resetShield(Shield* shield);

	// Function to get random x position for the shield
	int getRandomXPosForShield();

	CREATE_FUNC(SpawnManager);

private:	
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;	
	std::vector<Enemy*> m_vpActiveEnemies;
	bool m_bIsSpawned;

	// Bool variable to set if the shield is spawned
	bool m_bIsShieldSpawned;

	// Vector to hold shields
	std::vector<Shield*> m_vpShields;

	// Vector to hold active shields
	std::vector<Shield*> m_vpActiveShields;

	WorldManager* m_pWorldManager;
	CollisionManager* m_pCollisionManager;

};

#endif