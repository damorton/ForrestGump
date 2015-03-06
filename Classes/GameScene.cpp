#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "Player.h"
#include "Pause.h"

USING_NS_CC;

Scene* GameScene::createScene()
{	
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);	
	scene->getPhysicsWorld()->setGravity(Vec2(0, -300));
	scene->setTag(TAG_GAME_SCENE);

	GameScene* gameLayer = GameScene::create();
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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/Ambler.wav", true);

	// game play layer
	gamePlayLayer = Layer::create();
	this->addChild(gamePlayLayer, 0, TAG_GAME_LAYER);

	// HUD layer
	m_HudLayer = HUD::create();
	gamePlayLayer->addChild(m_HudLayer, 1, TAG_HUD);

	// segment spawns
	m_pCollectableFactory = CollectableFactory::create();
	gamePlayLayer->addChild(m_pCollectableFactory, 0, TAG_SEGMENT_MANAGER);

	//Background
	m_pParallax = Parallax::create();
	gamePlayLayer->addChild(m_pParallax, -1, "parallax");
	m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png", "background/backgroundFourth.png", "background/floorBoundaries.png");
	
	//Player
	Player* playerSprite = Player::create("sprites/Playersmall.png");
	gamePlayLayer->addChild(playerSprite, 1);

	// Spawn manager
	m_pSpawnManager = SpawnManager::create();
	gamePlayLayer->addChild(m_pSpawnManager, 0);
		
	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void GameScene::update(float delta)
{
	//CCLOG("-------------GAME LOOP START--------------");	

		
	CollisionManager::getInstance()->checkCollisions();
	WorldManager::getInstance()->getPlayer()->update();
	m_pCollectableFactory->update();		
	m_pParallax->update();
	m_pSpawnManager->update();

	CollisionManager::getInstance()->checkCollisions();

	m_HudLayer->update();

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
	CCLOG("GameOver");	
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);
}

void GameScene::pauseGame()
{
	// create a sprite that says simply 'Paused'
	pausedSprite = CCSprite::create("background/Splash.png"); // sprite image
	// create the paused sprite and paused menu buttons off screen
	pausedSprite->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);
	// add the Paused sprite and menu to the current layer
	this->addChild(pausedSprite, 100);

	auto resumeButton = MenuItemImage::create("buttons/btNotResumeGame.png", "buttons/btActResumeGame.png", CC_CALLBACK_1(GameScene::resumeGame, this));
	auto mainMenuButton = MenuItemImage::create("buttons/btNotMainGame.png", "buttons/btActMainGame.png", CC_CALLBACK_1(GameScene::mainGame, this));
	auto exitButton = MenuItemImage::create("buttons/exit.png", "buttons/exit_clicked.png", CC_CALLBACK_1(GameScene::exit, this));

	// create menu and add menu items
	pausedMenu = Menu::create(resumeButton, mainMenuButton, exitButton, NULL);	
	pausedSprite->addChild(pausedMenu, 3);

	

	

	/*
	CCLOG("Pause");
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));

	// to play sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);
	*/
}

void GameScene::resumeGame(cocos2d::Ref *pSender)
{
	CCLOG("ResumeGame");	
	Director::getInstance()->popScene();
}

void GameScene::mainGame(cocos2d::Ref *pSender)
{
	CCLOG("MainGame");
	Director::getInstance()->popScene();
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void GameScene::exit(cocos2d::Ref *pSender)
{
	//exit game
	Director::sharedDirector()->end();
}

void GameScene::cleanup()
{
	CollisionManager::getInstance()->cleanUp();
}
