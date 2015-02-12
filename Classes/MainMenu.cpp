#include "MainMenu.h"
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
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// particle testing 
	CCParticleSystem *ccEmitter = CCParticleSystemQuad::create("Flower.plist");
	ccEmitter->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 4));
	ccEmitter->setDuration(0.20);
	this->addChild(ccEmitter);

	// particle testing 
	CCParticleSystem *ccEmitter2 = CCParticleSystemQuad::create("Flower.plist");
	ccEmitter2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 8) * 2));
	ccEmitter2->setDuration(0.20);
	this->addChild(ccEmitter2);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_menu.wav", true);
	
	auto mainMenuBackground = Sprite::create("background/MainMenuBackground.png"); // sprite image
	mainMenuBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mainMenuBackground, -50); // add child

	// create the main menu items
	auto playButton = MenuItemImage::create("buttons/PlayNormal.png", "buttons/PlaySelected.png", CC_CALLBACK_1(MainMenu::play, this));
	auto highscoresButton = MenuItemImage::create("buttons/TrophyNormal.png", "buttons/TrophySelected.png", CC_CALLBACK_1(MainMenu::highscores, this));
	auto settingsButton = MenuItemImage::create("settings2.png", "settings2.png",CC_CALLBACK_1(MainMenu::settings, this)); // push the high scores scene	
	
	// position the menu buttons on screen
	playButton->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 8) * 2));
	highscoresButton->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 4));
	settingsButton->setPosition(Point(visibleSize.width / 4, (visibleSize.height / 5) * 2));

	// create menu and add menu items
	auto* menu = Menu::create(playButton, highscoresButton, settingsButton, NULL);

	// position the main menu
	menu->setPosition(Vec2::ZERO);

	// add the menu to the scene
	this->addChild(menu);

    return true;
}

void MainMenu::mainMenu()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);

	// delay opening of game scene to hear the button sound effects
	std::chrono::seconds duration(1);
	std::this_thread::sleep_for(duration); // Sleep for 2 seconds.
}

void MainMenu::playGame(cocos2d::Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	// to playGame sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);	


	// delay opening of game scene to hear the button sound effects
	std::chrono::seconds duration(1);
	std::this_thread::sleep_for(duration); // Sleep for 1 seconds.
}

void MainMenu::leaderboard(cocos2d::Ref *pSender)
{
	//Director::getInstance()->replaceScene(TransitionFade::create(1, Leaderboard::createScene()));
	// to playGame sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);

	// delay opening of game scene to hear the button sound effects
	std::chrono::seconds duration(1);
	std::this_thread::sleep_for(duration); // Sleep for 2 seconds.
}

void MainMenu::settings(cocos2d::Ref *pSender)
{	
	//Director::getInstance()->replaceScene(TransitionFade::create(1, Settings::createScene()));

	// to playGame sound effect if button is pressed 
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button-21.wav", false, 1.0f, 1.0f, 1.0f);

	// delay opening of game scene to hear the button sound effects
	std::chrono::seconds duration(1);
	std::this_thread::sleep_for(duration); // Sleep for 2 seconds.
}
