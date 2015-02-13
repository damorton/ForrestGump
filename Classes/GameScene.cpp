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
		
	//HUD* hudLayer = HUD::create();
	//scene->addChild(hudLayer, 1, TAG_HUD);

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
	this->initializeGame();
	return true;
}

bool GameScene::initializeGame()
{	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_action_1.wav", true);

	// game play layer
	gamePlayLayer = Layer::create();
	this->addChild(gamePlayLayer, 0, "gamePlayLayer");

	// HUD layer
	m_HudLayer = HUD::create();
	this->addChild(m_HudLayer, 1, "hudLayer");

	//Background
	m_pParallax = Parallax::create();
	gamePlayLayer->addChild(m_pParallax, 0, "parallax");
	//WorldManager::getInstance()->gameLayer()->addChild(m_pParallax, 0, "parallax");	
	if(m_pParallax->addBackground("background/backgroundFirst.png", "background/backgroundSecond.png", "background/backgroundThird.png"))
		CCLOG("Images loaded successful");	
	//gamePlayLayer->addChild(m_pParallax->m_pSpriteBackgroundFirst, 1);
	//gamePlayLayer->addChild(m_pParallax->m_pSpriteBackgroundSecond, -1);
	//gamePlayLayer->addChild(m_pParallax->m_pSpriteBackgroundThird, -2);
	//It works, but as I said, the Layer comes from Parallax without the plans, they are background, 
	//without the clouds and floor foreground effects!!!!!!!!!!!!!!!!!!!
	//gamePlayLayer->addChild(m_pParallax->loadBackground());

	// add floorSprite to game scene
	auto floorSprite = Sprite::create("foreground/floorSprite.png");
	floorSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, floorSprite->getContentSize().height / 2 + origin.y));
	auto floorEdgeBody = PhysicsBody::createEdgeBox(floorSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	floorSprite->setPhysicsBody(floorEdgeBody);
	floorSprite->getPhysicsBody()->setDynamic(false);
	gamePlayLayer->addChild(floorSprite, -1); // add at z:1 for floorSprite
	//WorldManager::getInstance()->gameLayer()->addChild(floorSprite, -1); // add at z:1 for floorSprite
	WorldManager::getInstance()->setFloorSprite(floorSprite);
		
	// Player			
	Player* playerSprite = Player::create("sprites/Player.png");		
	playerSprite->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, FLOOR_SPRITE_TOP);
	auto playerPhysicsBody = PhysicsBody::createBox(playerSprite->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	playerSprite->setPhysicsBody(playerPhysicsBody);
	playerPhysicsBody->setDynamic(false);
	gamePlayLayer->addChild(playerSprite, 0);
	//WorldManager::getInstance()->gameLayer()->addChild(playerSprite, 0);
	WorldManager::getInstance()->setPlayer(playerSprite);

	// creating spawn manager
	m_pSpawnManager = SpawnManager::create();
	// adding spawn manager to the game scene
	gamePlayLayer->addChild(m_pSpawnManager, 0);
		
	// segment spawns	
	spawnSegmentTimer = 0;
	//m_pSegmentManager = SegmentManager::create();
	//this->addChild(m_pSegmentManager);
	//m_pSegmentManager->spawnSegment();


	// pause button
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(GameScene::pause, this));
	menu_item_pause->setPosition(Vec2(origin.x + visibleSize.width - menu_item_pause->getContentSize().width / 2,
		origin.y + visibleSize.height - menu_item_pause->getContentSize().height / 2));

	// create menu, add menu items and add to the game scene
	auto* menu = Menu::create(menu_item_pause, NULL);
	menu->setPosition(Point(0, 0));
	m_HudLayer->addChild(menu);

	// touch controls
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
			
	m_fSpeed = 5.0f;

	// creating a schedule to control enemey spawns in delta time
	this->schedule(schedule_selector(GameScene::spawnEnemy), ENEMY_SPAWN_FREQ * visibleSize.width);

	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
	return true;
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
		//this->addChild(m_pSegment->spawnSegment());
		spawnSegmentTimer = 0;
	}

	WorldManager::getInstance()->getPlayer()->update();
	m_HudLayer->updateScore();
	//WorldManager::getInstance()->hudLayer()->updateScore();
	/*
	Parallax::getInstance()->scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);
	Parallax::getInstance()->scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, (m_fSpeed / 2));
	Parallax::getInstance()->scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, ((m_fSpeed / 5) - 0.8));
	*/

	//running animation
	
	this->runAction(AnimationMoves::getAnimationWithFrames(1, 2));

	CCLOG("Parallax");
	//FOCUS ON HERE
	//NOT WORKING THIS FUNCTION updateBackground() , uncomment and run, it is like Parallax.cpp dont find the images, something like it
	m_pParallax->updateBackground();
	
	//IMAGES ARE NOT BEING SEEN BY PARALLAX, THEY ARE LOADED, IAM USING m_Parallax BUT IT DOESNT WORK
	//m_pParallax->scrollBackground(m_pParallax->m_pSpriteBackgroundFirst, m_pParallax->m_pSpriteBackgroundFirst1, m_fSpeed);
		
	
//	m_pParallax->scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);
//	m_pParallax->scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, (m_fSpeed / 2));
//	m_pParallax->scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, ((m_fSpeed / 5) - 0.8));	

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

// calling this function to spawn enemies
void GameScene::spawnEnemy(float dt)
{
	enemey1.spawnEnemy(this);
}


void GameScene::pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));

	// to play sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);
}