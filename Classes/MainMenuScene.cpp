#include "MainMenuScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
	
    // add layer as a child to scene
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto mainMenuBackground = Sprite::create("background/MainMenuBackground.png"); // sprite image
	mainMenuBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mainMenuBackground, -50); // add child

	// create the main menu items
	auto playButton = MenuItemImage::create("buttons/PlayNormal.png", "buttons/PlaySelected.png", CC_CALLBACK_1(MainMenu::Play, this));
	auto highscoresButton = MenuItemImage::create("buttons/TrophyNormal.png", "buttons/TrophySelected.png", CC_CALLBACK_1(MainMenu::Highscores, this));
	//auto menu_item_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(MainMenu::Highscores, this)); // push the high scores scene	
	//auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenu::Settings, this)); // push the settings scene	
	

	// position the menu buttons on screen
	playButton->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
	highscoresButton->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 2));
	//menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
	//menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2));
	//menu_item_4->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 1));

	// create menu and add menu items
	auto* menu = Menu::create(playButton, highscoresButton, NULL);

	// position the main menu
	menu->setPosition(Vec2::ZERO);

	// add the menu to the scene
	this->addChild(menu);

    return true;
}

/* 
	Play button creates a new game scene and replaces the main menu.

	@param cocos2d::Ref *pSender pointer used by the engine
*/
void MainMenu::Play(cocos2d::Ref *pSender)
{
	CCLOG("Play");
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}

/*
	Highscores button creates the highscores scene to display the current scores for 
	players who have previously played the game.

	@param cocos2d::Ref *pSender pointer used by the engine
*/
void MainMenu::Highscores(cocos2d::Ref *pSender)
{
	CCLOG("Highscores");
	//auto scene = MainMenu::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


/*
	Settings button creates the settings scene to modify how the game is rendered and
	played.

	@param cocos2d::Ref *pSender pointer used by the engine
*/
void MainMenu::Settings(cocos2d::Ref *pSender)
{
	CCLOG("Settings");	
	//auto scene = MainMenu::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


/*
	ImageButton is an example of how an image can be used as a button.

	@param cocos2d::Ref *pSender pointer used by the engine
*/
void MainMenu::ImageButton(cocos2d::Ref *pSender)
{
	CCLOG("IMAGE Button");
	//auto scene = MainMenu::createScene();
	//Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}



void MainMenu::menuCloseCallback(Ref* pSender)
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
