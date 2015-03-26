#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"
#include "Definitions.h"
#include "CollisionManager.h"
#include "Player.h"
#include <iostream>

/* ---------------------------------------------------------------------------
** SpawnManager.h
**
** Description: Handles enemy spawns within the game.
**
** Author: Donnchadh Murphy, David Morton, Georgina Sheehan, Tiago Oliveira
**-------------------------------------------------------------------------*/

class SpawnManager : public cocos2d::Layer
{
public:	
	/* @brief init function that creates our enemies and seeds a random number */
	bool init();
	/* @brief SpawnManager deconstructor */
	virtual ~SpawnManager(){ this->spawnManagerCleanup(); };
	/* @brief SpawnManager cleanup releases our enemy resources */
	virtual void spawnManagerCleanup();
	/* @brief updates enemies */
	void update();
	/* @brief adds enemy to vector and sets bool to spawned */
	bool spawnEnemy();
	/* @brief generates a random y value for enemies */
	int getRandomHeight();
	/* @brief generates a random x value for enemies */
	int getRandomXPos();
	/* @brief gets the current number of spawned enemies */
	int getEnemyCount();
	/* @brief adds enemy to active vector and sets enemy to visible
	   @param enemy object
	*/
	bool addEnemyToActiveVector(Enemy* enemy);
	/* @brief defines the enemy movement behaviour */
	void moveSprites();
	/* @brief resets the enemey positon to a random x and y */
	void resetEnemy(Enemy* enemy);
	/* @brief creates all enemies within the game */
	void createEnemies();
	/* @brief gets the resource filepath and creates an enemy, positions are also set here
	   @param filepath, enemy name, gravity bool, rotation bool
	*/
	void createEnemy(std::string filename, std::string name, bool gravity, bool rotate);
	/* @brief pauses all enemies and their actions */
	void pauseGame();
	/* @brief resumes all enemies and their actions */
	void resumeGame();

	CREATE_FUNC(SpawnManager); // creating SpawnManager function

private:
	Player* m_pPlayer; // reference to player object
	std::vector<Enemy*> m_vpEnemies; // reference to vector of enemies	
	std::vector<Enemy*> m_vpActiveEnemies; // reference to vector of active enemies
	bool m_bIsSpawned; // bool to show if an enemy is spawned or not
};

#endif