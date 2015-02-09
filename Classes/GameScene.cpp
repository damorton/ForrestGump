#include "GameScene.h"
#include "Definitions.h"
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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // draw debug lines around objects in the world	
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

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_action_1.wav", true);

	//CCLOG("Game scene : %f x %f", visibleSize.width, visibleSize.height);
	
	// game play layer
	gamePlayLayer = Layer::create();
	this->addChild(gamePlayLayer, 0, "gamePlayLayer");

	// HUD layer
	m_cHud = HUD::create();
	this->addChild(m_cHud, 1, "hudLayer");

	
	// background 1 - Floor and clouds
	backgroundA = CCSprite::create("background/backgroundFirst.png"); 
	backgroundB = CCSprite::create("background/backgroundFirst2.png"); 
	backgroundA->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundB->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));	
	gamePlayLayer->addChild(backgroundA, 1); // add child
	gamePlayLayer->addChild(backgroundB, 1); // add child

	// background 2
	backgroundC = CCSprite::create("background/backgroundSecond.png");
	backgroundD = CCSprite::create("background/backgroundSecond2.png");
	backgroundC->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundD->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	gamePlayLayer->addChild(backgroundC, -1); // add child
	gamePlayLayer->addChild(backgroundD, -1); // add child

	// background 3
	backgroundE = CCSprite::create("background/backgroundThird.png");
	backgroundF = CCSprite::create("background/backgroundThird2.png");
	backgroundE->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundF->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));
	gamePlayLayer->addChild(backgroundE, -2); // add child
	gamePlayLayer->addChild(backgroundF, -2); // add child

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
	playerSprite->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, FLOOR_SPRITE_TOP);
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
			
	speed = 5.0f;

	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta)
{
	CCLOG("-------------GAME LOOP START--------------");	

	WorldManager::getInstance()->getPlayer()->update();
	m_cHud->updateScore();
	
	ScrollBackground();
	
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

void GameScene::ScrollBackground()
{
	backgroundA->setPosition(Vec2(backgroundA->getPosition().x - speed, backgroundA->getPosition().y));
	backgroundB->setPosition(Vec2(backgroundB->getPosition().x - speed, backgroundB->getPosition().y));

	if (backgroundA->getPosition().x < -backgroundA->getContentSize().width / 2){
		backgroundA->setPosition(Vec2(backgroundB->getPosition().x + backgroundB->getContentSize().width, backgroundA->getPosition().y));
	}
	if (backgroundB->getPosition().x < -backgroundB->getContentSize().width / 2){
		backgroundB->setPosition(Vec2(backgroundA->getPosition().x + backgroundA->getContentSize().width, backgroundB->getPosition().y));
	}


	backgroundC->setPosition(Vec2(backgroundC->getPosition().x - (speed / 2), backgroundC->getPosition().y));
	backgroundD->setPosition(Vec2(backgroundD->getPosition().x - (speed / 2), backgroundD->getPosition().y));

	if (backgroundC->getPosition().x < -backgroundC->getContentSize().width / 2){
		backgroundC->setPosition(Vec2(backgroundD->getPosition().x + backgroundD->getContentSize().width, backgroundC->getPosition().y));
	}
	if (backgroundD->getPosition().x < -backgroundD->getContentSize().width / 2){
		backgroundD->setPosition(Vec2(backgroundC->getPosition().x + backgroundC->getContentSize().width, backgroundD->getPosition().y));
	}



	backgroundE->setPosition(Vec2(backgroundE->getPosition().x - ((speed / 5) - 0.8), backgroundE->getPosition().y));
	backgroundF->setPosition(Vec2(backgroundF->getPosition().x - ((speed / 5) - 0.8), backgroundF->getPosition().y));

	if (backgroundE->getPosition().x < -backgroundE->getContentSize().width / 2){
		backgroundE->setPosition(Vec2(backgroundF->getPosition().x + backgroundF->getContentSize().width, backgroundE->getPosition().y));
	}
	if (backgroundF->getPosition().x < -backgroundD->getContentSize().width / 2){
		backgroundF->setPosition(Vec2(backgroundE->getPosition().x + backgroundE->getContentSize().width, backgroundF->getPosition().y));
	}

}



void GameScene::Pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));

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