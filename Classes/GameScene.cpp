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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // draw debug lines around objects in the world		
	scene->setTag(TAG_GAME_SCENE);

	GameScene* gameLayer = GameScene::create();
	gameLayer->SetPhysicsWorld(scene->getPhysicsWorld()); // set the layers physics
	scene->addChild(gameLayer, 0, TAG_GAME_LAYER);
	
	//SegmentManager* segmentManager = SegmentManager::create();
	//scene->addChild(segmentManager, 0, TAG_SEGMENT_MANAGER);

	HUD* hudLayer = HUD::create();
	scene->addChild(hudLayer, 1, TAG_HUD);
		
	//Pause* pause = Pause::create();
	//scene->addChild(pause, 1, TAG_PAUSE);	
	
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}	
	
	return true;
}

void GameScene::onEnter()
{
	this->initializeGame();
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
	this->addChild(floorSprite); 
	WorldManager::getInstance()->setFloorSprite(floorSprite);

	// Player			
	Player* playerSprite = Player::create("sprites/Player.png");
	playerSprite->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, FLOOR_SPRITE_TOP);	
	//auto playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);	
	//playerPhysicsBody->setDynamic(false);	
	//playerSprite->setPhysicsBody(playerPhysicsBody);
	this->addChild(playerSprite);
	WorldManager::getInstance()->setPlayer(playerSprite);
	CollisionManager::getInstance()->registerPlayer(playerSprite);
	
	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	this->scheduleUpdate();
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	CCLOG("onContactBegin -------> ");			
	return true;
}

void GameScene::update(float delta)
{
	CCLOG("-------------GAME LOOP START--------------");	
	
	// update
	WorldManager::getInstance()->getPlayer()->update();
	WorldManager::getInstance()->hudLayer()->update();
	//WorldManager::getInstance()->segmentManagerLayer()->update();

	//CollisionManager::getInstance()->checkCollisions();
		
	backgroundA->setPosition(Vec2(backgroundA->getPosition().x - 10, backgroundA->getPosition().y));
	backgroundB->setPosition(Vec2(backgroundB->getPosition().x - 10, backgroundB->getPosition().y));

	if (backgroundA->getPosition().x < -backgroundA->getContentSize().width / 2){
		backgroundA->setPosition(Vec2(backgroundB->getPosition().x + backgroundB->getContentSize().width, backgroundA->getPosition().y));
	}
	if (backgroundB->getPosition().x < -backgroundB->getContentSize().width / 2){
		backgroundB->setPosition(Vec2(backgroundA->getPosition().x + backgroundA->getContentSize().width, backgroundB->getPosition().y));
	}		
	
	CCLOG("-------------GAME LOOP END--------------");
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

void GameScene::pause()
{
	CCLOG("Pause");
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));

	// to play sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);
}