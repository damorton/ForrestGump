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
	scene->getPhysicsWorld()->setUpdateRate(0.3f);
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
	auto winSize = Director::getInstance()->getWinSize(); // added for player spawn position

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_action_1.wav", true);

	CCLOG("Game scene : %f x %f", visibleSize.width, visibleSize.height);
	
	// game play layer
	gamePlayLayer = Layer::create();
	this->addChild(gamePlayLayer, 0, "gamePlayLayer");

	// HUD layer
	m_cHud = HUD::create();
	this->addChild(m_cHud, 1, "hudLayer");

	// Background
	auto gameBackground = Sprite::create("background/gameBackground.png"); // sprite image
	gameBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	gamePlayLayer->addChild(gameBackground, -1); // add child
	

	// add floorSprite to game scene
	auto floorSprite = Sprite::create("foreground/floorSprite.png");
	floorSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, floorSprite->getContentSize().height / 2 + origin.y));
	auto floorEdgeBody = PhysicsBody::createEdgeBox(floorSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	floorSprite->setPhysicsBody(floorEdgeBody);
	floorSprite->getPhysicsBody()->setDynamic(false);
	gamePlayLayer->addChild(floorSprite, 0); // add at z:1 for floorSprite
	WorldManager::getInstance()->setFloorSprite(floorSprite);

	/*
	Maze* mazeLayer = Maze::create();
	mazeLayer->addTMXTileMap("maps/maze.tmx");
	mazeLayer->addPhysicsEdgeBox();
	mazeLayer->addPhysicsToTiles("maze");
	gamePlayLayer->addChild(mazeLayer, 0, "maze");
	*/
		
	// Player			

	Player* playerSprite = Player::create("sprites/Player.png");		
	playerSprite->setPosition(Vec2(((visibleSize.width / 3) * 1) + origin.x,		
	WorldManager::getInstance()->getFLoorSprite()->getPositionY() + 		
	playerSprite->getContentSize().height / 2));
	auto playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	playerSprite->setPhysicsBody(playerPhysicsBody);
	playerPhysicsBody->setDynamic(false);
	gamePlayLayer->addChild(playerSprite, 0);
	WorldManager::getInstance()->setPlayer(playerSprite);
		
	// pause button
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(GameScene::Pause, this));
	menu_item_pause->setPosition(Vec2(origin.x + visibleSize.width - menu_item_pause->getContentSize().width/2,
		origin.y + visibleSize.height - menu_item_pause->getContentSize().height / 2));
	
	// create menu, add menu items and add to the game scene
	auto *menu = Menu::create(menu_item_pause, NULL);
	menu->setPosition(Point(0, 0));
	m_cHud->addChild(menu);

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
	CCLOG("-------------GAME LOOP START--------------");	
	WorldManager::getInstance()->getPlayer()->update();
	m_cHud->updateScore();
	
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

/*
	Passing the location the user touched into the player function to check for a jump
*/
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) 
{
	WorldManager::getInstance()->getPlayer()->touch(locationInGLFromTouch(*touch));
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

	// to play sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);
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