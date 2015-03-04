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
	//playerSprite->setScale(2.0);
	gamePlayLayer->addChild(playerSprite, 1);

	// Spawn manager
	m_pSpawnManager = SpawnManager::create();
	gamePlayLayer->addChild(m_pSpawnManager, 0);
		
	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

			
	//m_fSpeed = 5.0f;

	
	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
	//this->schedule(schedule_selector(SpawnManager::spawnEnemy), 0.0029f * VISIBLE_SIZE_WIDTH);
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
	m_HudLayer->update();
	m_pParallax->update();
	m_pSpawnManager->update();

	//CCLOG("-------------GAME LOOP END--------------");

}

/*
	This function converts each touch the user does into a Point(x, y)
*/
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

void GameScene::cleanup()
{
	CollisionManager::getInstance()->cleanUp();
}
