#include "PauseScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
	auto pauseMenuBackground = Sprite::create("background/pauseMenuBackground.png"); // sprite image
	pauseMenuBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(pauseMenuBackground, -50); // add child
	
	// create the Pause menu items
	auto resumeButton = MenuItemImage::create("buttons/resume.png", "buttons/resume_clicked.png", CC_CALLBACK_1(PauseScene::Resume, this));
	auto mainMenuButton = MenuItemImage::create("buttons/menu.png", "buttons/menu_clicked.png", CC_CALLBACK_1(PauseScene::MainMenu, this));
	auto exitButton = MenuItemImage::create("buttons/exit.png", "buttons/exit_clicked.png", CC_CALLBACK_1(PauseScene::Exit, this));
    
	// position the menu buttons on screen
	resumeButton->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3) + 150));
	mainMenuButton->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3)));
	exitButton->setPosition(Point(visibleSize.width - 50, (visibleSize.height / 3)-100));
	
	// create menu and add menu items
	auto* menu = Menu::create(resumeButton, mainMenuButton, exitButton, NULL);
	menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

/*
	Resume button pops the pause scene and returns to the game scene

	@param cocos2d::Ref *pSender pointer used by the engine
*/
void PauseScene::Resume(cocos2d::Ref *pSender)
{
	// pop pause scene
    Director::getInstance()->popScene();		
}

/*
	Main menu button pops the pause scene and then replaces the game scene with 
	a new main menu scene.
	
	@param cocos2d::Ref *pSender pointer used by the engine
*/
void PauseScene::MainMenu(cocos2d::Ref *pSender)
{
	// pop screen & replace game scene
	Director::getInstance()->popScene();
    auto scene = MainMenu::createScene();    
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}


void PauseScene::Exit(cocos2d::Ref *pSender)
{
	//exit game
	Director::sharedDirector()->end();
}


void PauseScene::menuCloseCallback(Ref* pSender)
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
