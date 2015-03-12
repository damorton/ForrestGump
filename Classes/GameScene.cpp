#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Player.h"

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
	gamePlayLayer = Layer::create();
	this->addChild(gamePlayLayer, 0, TAG_GAME_LAYER);
	
	//Background
	m_pParallax = Parallax::create();
	this->addChild(m_pParallax, -1, "parallax");
	m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png", "background/backgroundFourth.png", "background/floorBoundaries.png");

	//Player
	playerSprite = Player::create("sprites/playerRunning01.png");
	this->addChild(playerSprite, 1);
		
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


	m_bPaused = false;

	this->scheduleUpdate();	
	CCLOG("Game scene initialized");
	return true;
}

/*void GameScene::addScreenShake()
{	
	auto jump = JumpBy::create(1, Point(1000, 1000), 0.5, 5);
	auto reverse = jump->reverse();	
	this->runAction(jump);
	this->runAction(reverse);	
}*/

void GameScene::update(float delta)
{
	//CCLOG("-------------GAME LOOP START--------------");	
	// Game world speed
	if (WorldManager::getInstance()->getPlayer()->getDistance() < 6000 && WorldManager::getInstance()->getPlayer()->getDistance() % 500 == 0)
	{
		WorldManager::getInstance()->increaseGameWorldSpeed();
		WorldManager::getInstance()->increaseEnemyMovementSpeed();
	}

	WorldManager::getInstance()->getPlayer()->update();
	m_pSpawnManager->update();
	m_pCollectableFactory->update();
	m_pParallax->update();
	m_HudLayer->update();
	
	CollisionManager::getInstance()->checkCollisions();

	//CCLOG("-------------GAME LOOP END--------------");
}

inline Point locationInGLFromTouch(Touch& touch)
{
	auto director = Director::getInstance();
	return director->convertToGL(touch.getLocationInView());
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	WorldManager::getInstance()->getPlayer()->touch(locationInGLFromTouch(*touch));
	return true;
}

void GameScene::gameOver()
{	
	CCLOG("Game Scene: Game over called");
	this->pauseGame();	
	// Death sequence here!!
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}

void GameScene::mainMenu()
{
	CCLOG("Game Scene: Main menu called");
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}

void GameScene::pauseGame()
{
	CCLOG("Game Scene: Pause game called");
	if (!m_bPaused)
	{
		m_bPaused = true;
		Director::getInstance()->getRunningScene()->pause();		
		playerSprite->pauseSchedulerAndActions();
		m_pSpawnManager->pauseGame();
		this->pauseSchedulerAndActions();			
	}
	else
	{
		m_bPaused = false;
		Director::getInstance()->getRunningScene()->resume();		
		playerSprite->resumeSchedulerAndActions();
		m_pSpawnManager->resumeGame();
		this->resumeSchedulerAndActions();				
	}
}
