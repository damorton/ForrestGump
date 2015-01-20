#include "GameScene.h"
#include "HelloWorldScene.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Game Scene", "Helvetica", 18);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "GameScene" splash screen"
    auto sprite = Sprite::create("foreground.png");
	WorldManager::getInstance()->getPlayer()->setSprite("Player.png");
	
	auto playerSprite = WorldManager::getInstance()->getPlayer()->getSprite();
	
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	this->addChild(playerSprite, 0);
	
	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
    return true;
}

/*
	The hello world upate function is calling the game managers
	update function 60 times per second or whatever the fps is set
	to. This is the game loop implementation because if a seperate loop was added to the 
	game managers update function the application would be caught in an infinite loop.

	@param delta time
*/
void GameScene::update(float delta){
	
	// call the game manager update function
	WorldManager::getInstance()->getGameManager()->update();
}


// pause the game and push the main menu scene
void GameScene::Pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");

	auto scene = HelloWorld::createScene();

	Director::getInstance()->pushScene(TransitionFlipX::create(2, scene));
}


void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
