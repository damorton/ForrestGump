#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

#include "cocos2d.h"
#include "Enemy.h"
#include "Definitions.h"
#include "CollisionManager.h"
#include "Player.h"
#include <iostream>
#include "Shield.h"

class SpawnManager : public cocos2d::Layer
{
public:	
	bool init();
	virtual ~SpawnManager(){ this->spawnManagerCleanup(); };
	virtual void spawnManagerCleanup();

	void update();
	bool spawnEnemy();
	int getRandomHeight();
	int getRandomXPos();
	int getEnemyCount();
	bool addEnemyToActiveVector(Enemy* enemy);
	void resetSprite(Node* sender, void* enemy);
	void moveSprites();
	void resetEnemy(Enemy* enemy);
	void createEnemies();
	void createEnemy(std::string filename, std::string name, bool gravity, bool rotate);
	void pauseGame();
	void resumeGame();

    /* @brief function to spawn shields */
	bool spawnShield();
    /* @brief function to create shields by passing in the filename */
	void createShields();
	/* @brief function to take in the arguments to create the shield and add it to spawn manager */
	void createShield(std::string filename, bool gravity, bool rotate);
    /* @brief function to add shield to the active vector 
	   @param filename, gravity, rotate 
	*/
	bool addShieldToActiveVector(Shield* shield);
    /* @brief function to move the shields 
	   @param Shield object
	*/
	void moveShields();
    /* @brief function to reset the shield */
	void resetShield(Shield* shield);
	/* @brief function to get random x position for the shield */
	int getRandomXPosForShield();

	CREATE_FUNC(SpawnManager);
private:	
	Player* m_pPlayer;
	std::vector<Enemy*> m_vpEnemies;	
	std::vector<Enemy*> m_vpActiveEnemies;
	bool m_bIsSpawned;
	bool m_bIsShieldSpawned; // bool variable to set if the shield is spawned
	std::vector<Shield*> m_vpShields; // vector to hold shields
	std::vector<Shield*> m_vpActiveShields; // vector to hold active shields
};

#endif