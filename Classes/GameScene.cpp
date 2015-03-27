/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	GameScene.cpp

	Description: Game Scene implementation

*/

// Includes
#include "GameScene.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "CollectableFactory.h"
#include "SpawnManager.h"
#include "Parallax.h"
#include "GameOver.h"
#include "MainMenu.h"
#include "HUD.h"
#include "Player.h"
#include "audio/include/SimpleAudioEngine.h"

Scene* GameScene::createScene()
{	
	// Creates scene with physics
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity((WorldManager::getInstance()->getGravity()));
	scene->setTag(TAG_GAME_SCENE);
	
	// Creates gameLayer with physics
	auto gameLayer = GameScene::create();
	scene->addChild(gameLayer, 0, TAG_GAME_LAYER);
	
	return scene;
}

// Init 
bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}	
	this->initializeGame();
	return true;
}
// Game Initialization 
bool GameScene::initializeGame()
{	

	// Initializes all game aspects
	m_pWorldManager = WorldManager::getInstance();
	m_pCollisionManager = CollisionManager::getInstance();
	m_pWorldManager->setGameWorldSpeed(WORLD_MOVEMENT_SPEED);
	m_pWorldManager->setEnemyMovementSpeed(ENEMY_MOVEMENT_SPEED);
	m_pWorldManager->setGravity(GRAVITATIONAL_FORCE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Plays Background Music for Game Scene
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/8bitDungeonLevel.wav", true);
	
	// Background
	m_pParallax = Parallax::create();
	this->addChild(m_pParallax, -1, "parallax");
	m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png", "background/backgroundFourth.png", "background/floorBoundaries.png");

	// Player
	m_pPlayer = Player::create("sprites/playerRunning01.png");
	this->addChild(m_pPlayer, 1);
		
	// HUD layer
	m_HudLayer = HUD::create();
	this->addChild(m_HudLayer, 1, TAG_HUD);

	// Collectables
	m_pCollectableFactory = CollectableFactory::create();
	this->addChild(m_pCollectableFactory, 0, TAG_SEGMENT_MANAGER);

	// Spawn manager
	m_pSpawnManager = SpawnManager::create();
	this->addChild(m_pSpawnManager, 0);
	
	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	// Game session timer
	m_nGameTime = 0;
	WorldManager::getInstance()->setTimePlayedSeconds(m_nGameTime);
	this->schedule(schedule_selector(GameScene::updateTimer), 1.0f);	
	
	// Initializes paused to false
	m_bPaused = false;

	this->scheduleUpdate();	
	//CCLOG("Game scene initialized");
	return true;
}

// Updates Game Timer
void GameScene::updateTimer(float dt)
{	
	m_nGameTime++;
	//CCLOG("Updating game timer : %d seconds", m_nGameTime);
}

// Updates Game Scene
void GameScene::update(float delta)
{
	//CCLOG("-------------GAME LOOP START--------------");	

	// Game world speed
	if (m_pWorldManager->getGameWorldSpeed() < MAX_GAME_SPEED && m_pPlayer->getDistance() % 500 == 0)
	{
		m_pWorldManager->increaseGameWorldSpeed();
		m_pWorldManager->increaseEnemyMovementSpeed();
	}

	m_pPlayer->update();	
	m_pSpawnManager->update();
	m_pCollectableFactory->update();
	m_pParallax->update();
	m_HudLayer->update();
	
	m_pCollisionManager->checkCollisions();
	
	//CCLOG("-------------GAME LOOP END--------------");
}

// Gets the Users Touch
inline Point locationInGLFromTouch(Touch& touch)
{
	auto director = Director::getInstance();
	return director->convertToGL(touch.getLocationInView());
}

// Sets Player to jump when screen is touched
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	if (!m_bPaused)
	{
		m_pPlayer->jump();
	}	
	return true;
}

// Goes to Game Over
void GameScene::gameOver()
{		
	this->pause();

	// Time played in game	
	WorldManager::getInstance()->setTimePlayedSeconds(m_nGameTime);	

	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
	
}

// Goes to main menu
void GameScene::mainMenu()
{
	// Pause game layer
	this->pause();

	// Unpause director
	this->pauseGame();
	
	// Move to Main Menu
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene()));	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);		
}

// Pauses Game
void GameScene::pauseGame()
{
	if (!m_bPaused)
	{
		m_bPaused = true;	
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		Director::getInstance()->pause();
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setAutoStep(false);		
	}
	else
	{
		m_bPaused = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setAutoStep(true);		
	}
}
