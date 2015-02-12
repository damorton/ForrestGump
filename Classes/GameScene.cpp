#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "EndScene.h"
#include "Player.h"

USING_NS_CC;

typedef std::shared_ptr<Player> spPlayer;

Scene* GameScene::createScene()
{	
	auto scene = Scene::createWithPhysics();	
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // draw debug lines around objects in the world		
	scene->setTag(TAG_GAME_SCENE);

	auto gameLayer = GameScene::create();
	gameLayer->SetPhysicsWorld(scene->getPhysicsWorld()); // set the layers physics
	scene->addChild(gameLayer, 0, TAG_GAME_LAYER);
	
	auto hudLayer = HUD::create();
	scene->addChild(hudLayer, 1, TAG_HUD);
	return scene;
}

void GameScene::onEnterTransitionDidFinish()
{
	this->initializeGame();
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}	
	return true;
}

void GameScene::initializeGame()
{	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_action_1.wav", true);
	
	
	
	// background 3
	backgroundA = CCSprite::create("background/gameBackground.png");
	backgroundB = CCSprite::create("background/gameBackground2.png");
	backgroundA->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundB->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backgroundA, -3); // add child
	this->addChild(backgroundB, -3); // add child

	// background 2

	// background 1	

	// add floorSprite to game scene
	auto floorSprite = Sprite::create("foreground/floorSprite.png");
	floorSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, floorSprite->getContentSize().height / 2 + origin.y));
	auto floorEdgeBody = PhysicsBody::createEdgeBox(floorSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	floorSprite->setPhysicsBody(floorEdgeBody);
	floorSprite->getPhysicsBody()->setDynamic(false);
	this->addChild(floorSprite, 0); // add at z:1 for floorSprite
	WorldManager::getInstance()->setFloorSprite(floorSprite);

	// Player			
	Player* playerSprite = Player::create("sprites/Player.png");
	playerSprite->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, FLOOR_SPRITE_TOP);

	auto playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);

	playerPhysicsBody->setDynamic(false);
	playerPhysicsBody->setCategoryBitmask(0x02);
	playerPhysicsBody->setCollisionBitmask(0x01);
	playerPhysicsBody->setContactTestBitmask(true);
	playerSprite->setPhysicsBody(playerPhysicsBody);

	this->addChild(playerSprite, 0);
	WorldManager::getInstance()->setPlayer(playerSprite);
	CollisionManager::getInstance()->registerPlayer(playerSprite);

	// segment spawns
	spawnSegmentTimer = 0;
	m_pSegment = Maze::create();
	m_pSegment->addTMXTileMap("maps/CoinSegmentA.tmx");
	this->addChild(m_pSegment->spawnSegment());
	
	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	speed = 5.0f;

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
}



bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	CCLOG("onContactBegin -------> ");			
	return true;
}

void GameScene::update(float delta)
{
	//CCLOG("-------------GAME LOOP START--------------");	
	spawnSegmentTimer++;
	if (spawnSegmentTimer > 500)
	{
		CCLOG("Spawn segment");
		this->addChild(m_pSegment->spawnSegment());
		spawnSegmentTimer = 0;
	}

	// update the player
	WorldManager::getInstance()->getPlayer()->update();
	
	// update enemies

	// check for collisions
	CollisionManager::getInstance()->checkCollisions();

	WorldManager::getInstance()->hudLayer()->updateScore();
	
	backgroundA->setPosition(Vec2(backgroundA->getPosition().x - speed, backgroundA->getPosition().y));
	backgroundB->setPosition(Vec2(backgroundB->getPosition().x - speed, backgroundB->getPosition().y));

	if (backgroundA->getPosition().x < -backgroundA->getContentSize().width / 2){
		backgroundA->setPosition(Vec2(backgroundB->getPosition().x + backgroundB->getContentSize().width, backgroundA->getPosition().y));
	}
	if (backgroundB->getPosition().x < -backgroundB->getContentSize().width / 2){
		backgroundB->setPosition(Vec2(backgroundA->getPosition().x + backgroundA->getContentSize().width, backgroundB->getPosition().y));
	}		
	
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

void GameScene::Pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");
	auto scene = PauseScene::createScene();	
	Director::getInstance()->pushScene(scene);

	// to play sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);
}

void GameScene::EndGame(cocos2d::Ref *pSender)
{
	CCLOG("End Game");
	auto scene = EndScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	WorldManager::getInstance()->cleanUp(); // close world manager
	Director::getInstance()->end(); // close director 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}