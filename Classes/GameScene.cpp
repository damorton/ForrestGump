#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "Pause.h"
#include "Player.h"

USING_NS_CC;

Scene* GameScene::createScene()
{	
	auto scene = Scene::createWithPhysics();	
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

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Ambler.wav", true);

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

	if (m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png"))
	{
		CCLOG("Images loaded successful");
	}
	// CHANGE FLOOR SPRITE TO RECT FOR THE PLAYER POSITION
	auto floorSprite = Sprite::create("background/floorBoundaries.png");
	floorSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, floorSprite->getContentSize().height / 2 + origin.y));
	auto floorEdgeBody = PhysicsBody::createEdgeBox(floorSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	floorSprite->setPhysicsBody(floorEdgeBody);
	floorSprite->getPhysicsBody()->setDynamic(false);

	gamePlayLayer->addChild(floorSprite, 0); // add at z:1 for floorSprite	
	WorldManager::getInstance()->setFloorSprite(floorSprite);

	//Player
	Player* playerSprite = Player::create("sprites/Player.png");
	playerSprite->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, (WorldManager::getInstance()->getFloorSprite()->getContentSize().height + playerSprite->getContentSize().height / 2) - 5));
	auto playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	playerSprite->setPhysicsBody(playerPhysicsBody);
	playerPhysicsBody->setDynamic(false);
	gamePlayLayer->addChild(playerSprite, 0);

	//Start player walking
	playerSprite->getAnimationWithFrames();
	playerSprite->runAction(RepeatForever::create(playerSprite->animate));

	WorldManager::getInstance()->setPlayer(playerSprite);
	CollisionManager::getInstance()->setPlayer(playerSprite);

	// Spawn manager
	m_pSpawnManager = SpawnManager::create();
	gamePlayLayer->addChild(m_pSpawnManager, 0);
		
	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	// creating a schedule to control enemey spawns in delta time
	//this->schedule(schedule_selector(GameScene::spawnEnemy), ENEMY_SPAWN_FREQ * visibleSize.width);

	// call the schedule update in order to run this layers update function
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
	
	WorldManager::getInstance()->getPlayer()->update();
	m_pCollectableFactory->update();
	CollisionManager::getInstance()->checkCollisionsWithLayers();
	m_HudLayer->update();
	m_pParallax->updateBackground();
		
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
	//playerSprite->stopAllActions();
	//playerSprite->runAction(AnimationMoves::getAnimationWithFrames(1, 4));
	//hero->runAction(Utils::getAnimationWithFrames(9, 16));
	return true;
}

// calling this function to spawn enemies
void GameScene::spawnEnemy(float dt)
{
	m_enemey.spawnEnemy(this);
}


void GameScene::pause()
{
	CCLOG("Pause");
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);
}

void GameScene::cleanup()
{
	CollisionManager::getInstance()->cleanUp();
}