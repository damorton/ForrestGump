#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Player.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{	
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);	
	scene->getPhysicsWorld()->setGravity((WorldManager::getInstance()->getGravity()));
	scene->setTag(TAG_GAME_SCENE);
	
	auto gameLayer = GameScene::create();
	gameLayer->SetPhysicsWorld(scene->getPhysicsWorld()); // set the layers physics		
	scene->addChild(gameLayer, 0, TAG_GAME_LAYER);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}	
	this->initializeGame();
	return true;
}

bool GameScene::initializeGame()
{	
	WorldManager::getInstance()->setGameWorldSpeed(WORLD_MOVEMENT_SPEED);
	WorldManager::getInstance()->setEnemyMovementSpeed(ENEMY_MOVEMENT_SPEED);
	WorldManager::getInstance()->setGravity(GRAVITATIONAL_FORCE);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/8bitDungeonLevel.wav", true);
		

	// game play layer
	//gamePlayLayer = Layer::create();
	//this->addChild(gamePlayLayer, 0, TAG_GAME_LAYER);
	
	//Background
	m_pParallax = Parallax::create();
	this->addChild(m_pParallax, -1, "parallax");
	m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png", "background/backgroundFourth.png", "background/floorBoundaries.png");

	//Player
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
	
	m_bPaused = false;

	this->scheduleUpdate();	
	CCLOG("Game scene initialized");
	return true;
}

void GameScene::updateTimer(float dt)
{
	CCLOG("***************UPDATING GAME TIMER******************");
	m_nGameTime++;
}

void GameScene::update(float delta)
{
	CCLOG("-------------GAME LOOP START--------------");	
	CCLOG("-------------UPDATING GAME LAYER--------------");
	// Game world speed
	if (WorldManager::getInstance()->getGameWorldSpeed() < MAX_GAME_SPEED && m_pPlayer->getDistance() % 200 == 0)
	{
		WorldManager::getInstance()->increaseGameWorldSpeed();
		WorldManager::getInstance()->increaseEnemyMovementSpeed();
	}

	m_pPlayer->update();	
	m_pSpawnManager->update();
	m_pCollectableFactory->update();
	m_pParallax->update();
	m_HudLayer->update();
	
	CollisionManager::getInstance()->checkCollisions();
	
	CCLOG("-------------GAME LOOP END--------------");
}

inline Point locationInGLFromTouch(Touch& touch)
{
	auto director = Director::getInstance();
	return director->convertToGL(touch.getLocationInView());
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	if (!m_bPaused)
	{
		m_pPlayer->jump();
	}	
	return true;
}


void GameScene::gameOver()
{		
	CCLOG("Game Scene: Game over called");	
	//this->pauseGame();	
	//this->unschedule(schedule_selector(GameScene::updateTimer));
	// Time played in game	
	this->pause();
	WorldManager::getInstance()->setTimePlayedSeconds(m_nGameTime);	
	// Death sequence here!!
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));
	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
	
	//Director::getInstance()->resume();
	//Director::getInstance()->getRunningScene()->getPhysicsWorld()->setAutoStep(true);
}

void GameScene::mainMenu()
{
	CCLOG("Game Scene: Main menu called");
	// Pause game layer
	this->pause();

	// Unpause director
	this->pauseGame();
	
	// Move to Main Menu
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene()));	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);		
}

void GameScene::pauseGame()
{
	CCLOG("Game Scene: Pause game called");
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
