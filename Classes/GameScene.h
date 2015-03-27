/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	GameScene.h

	Description: Creates Game scene for the game

*/
#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

// Includes
#include "Definitions.h"

// Forward declarations
class WorldManager;
class CollisionManager;
class CollectableFactory;
class SpawnManager;
class Parallax;
class HUD;
class Player;
class Enemy;

class GameScene : public cocos2d::Layer
{
public:    
	// creates scene
    static Scene* createScene(); 

	// init function
    virtual bool init(); 

	// Create function for game scene
	CREATE_FUNC(GameScene);

	// Game Initialization
	bool initializeGame();

	// Update
	void update(float delta);	

	// Register screen touch
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);

	// Calls game over scene
	void gameOver();

	// Changes to main menu
	void mainMenu();

	// Pauses 
	void pauseGame();	

	// Updates Timer
	void updateTimer(float dt);
	
private:		
    // Variables for different types of objects to be created in Game Scene
	HUD* m_HudLayer;
	Parallax* m_pParallax;
	Player* m_pPlayer;
	CollectableFactory* m_pCollectableFactory;
	SpawnManager* m_pSpawnManager;
	WorldManager* m_pWorldManager;
	CollisionManager* m_pCollisionManager;

	int spawnSegmentTimer;
	bool m_bPaused;
    float m_nGameTime;
};

#endif // __GAMESCENE_SCENE_H__
