#include "GameScene.h"
#include "WorldManager.h"
#include "MainMenuScene.h"
#include "PauseScene.h"
#include "EndScene.h"
#include "Player.h"

USING_NS_CC;

typedef std::shared_ptr<Player> spPlayer;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // draw debug lines around objects in the world
	
	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld()); // set the layers physics

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CCLOG("Game scene : %f x %f", visibleSize.width, visibleSize.height);
		
	// create and initialize a label    	
	auto label = LabelTTF::create("Game Scene", "Segoe UI", FONT_SIZE);		
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);
		
	auto gameBackground = Sprite::create("background/gameBackground.png"); // sprite image
	gameBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(gameBackground, -50); // add child
		
	// TMX map
	auto mazeLayer = Layer::create();
	mazeLayer->setPosition(Vec2::ZERO); // center of game scene
	RotateBy* rotate = RotateBy::create(15.0f, 360);
	mazeLayer->runAction(RepeatForever::create(rotate));
	auto mazeTileMap = TMXTiledMap::create("maps/maze.tmx");
	//mazeTileMap->setPosition(Vec2::ZERO); // center of mapLayer
	auto mazePhysicsEdge = PhysicsBody::createEdgeBox(mazeTileMap->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 5);
	mazeTileMap->setPhysicsBody(mazePhysicsEdge); 	
	mazeLayer->addChild(mazeTileMap, 0, "TMXMaze");
		
	this->addChild(mazeLayer);
	
	// player		
	WorldManager::getInstance()->setPlayer(spPlayer(new Player())); // store shared pointer in world manager
	auto playerSprite = Sprite::create("sprites/Player.png"); // sprite image
	WorldManager::getInstance()->getPlayer()->setSprite(playerSprite); // set sprite
	playerSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto playerPhysicsBody = PhysicsBody::createCircle(playerSprite->getContentSize().width /2, PhysicsMaterial(1, 0, 1));
	playerSprite->setPhysicsBody(playerPhysicsBody);
	playerPhysicsBody->setDynamic(true);
	this->addChild(playerSprite, 10); // add child
	
	// pause button
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(GameScene::Pause, this));
	menu_item_pause->setPosition(Vec2(origin.x + visibleSize.width - menu_item_pause->getContentSize().width/2,
		origin.y + visibleSize.height - menu_item_pause->getContentSize().height / 2));
	
	// create menu, add menu items and add to the game scene
	auto *menu = Menu::create(menu_item_pause, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
		
	

	return true;
}

void GameScene::update(float delta)
{
	//CCLOG("-------------GAME LOOP START--------------");
	// call the player update
	//WorldManager::getInstance()->getPlayer()->update();
	
	//CCLOG("-------------GAME LOOP END--------------");
}

// TOUCH BEGIN
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{	
	WorldManager::getInstance()->getPlayer()->jump();
	return true;
}

/*
	Pause button creates a new pause scene and pushes it over the game scene
	
	@param cocos2d::Ref *pSender pointer used by the engine
*/
void GameScene::Pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));
}

/*
	EndGame button creates a new game game scene and replaces the game scene
	
	@param cocos2d::Ref *pSender pointer used by the engine
*/
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