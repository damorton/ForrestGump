
// includes
#include <iostream>
#include "GameManager.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Enemy.h"

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool GameManager::init()
{
	// get player, enemies and boss pointer from the WorldManager
	m_pPlayer = WorldManager::getInstance()->getPlayer();		
	m_pvEnemies = WorldManager::getInstance()->getEnemyVector();
	m_pBoss = WorldManager::getInstance()->getBoss();
		
	return true;
}

/*
	Main update method (game loop)
*/
void GameManager::update()
{	
#ifdef _DEBUG
	CCLOG("GameManager::update() called");
#endif

	/*
		The game managers game loop is not needed here because
		it is being called by the HelloWorld Scenes update function.

		Game loops are at the core of any game and are essential for 
		them to run. A game loop looks like this:

		void gameLoop()
		{
			while(game != DONE)				
			{
				getInputFromDevice();
				physicsEngineStep();
				updateGameWorld();
				render();
			}
			cleanUp();
		}


		The game loop will run until the game ends and the clean up
		is done to free any resources used by the game.

	*/
	CCLOG("-------------GAME LOOP START--------------");
	// call the player update
	m_pPlayer->update();
	
	// call the enemies update functions
	for (int i = 0; i < (int) m_pvEnemies.size(); i++)
	{
		// call each enemies update function
		m_pvEnemies.at(i)->update();
	}
	
	// call the boss update
	m_pBoss->update();

	for (int i = 0; i < (int) m_pvEnemies.size(); i++)
	{
		// calls each enemies runAI
		m_pvEnemies.at(i)->runAI();
	}

	// call the boss runAI
	m_pBoss->runAI();

	// calls the collision manager to check collisions
	CollisionManager::getInstance()->checkCollisons();

	// print statement "render"
	CCLOG("Render");
	CCLOG("-------------GAME LOOP END--------------");
}

void GameManager::cleanUp()
{
#ifdef _DEBUG
	CCLOG("GameManager::cleanUp() called");
#endif	
	// the game manager does not create any objects 
	// so none need to be deleted

}