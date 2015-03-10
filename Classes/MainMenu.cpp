#include "MainMenu.h"
#include "GameScene.h"
#include "WorldManager.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();    
    auto layer = MainMenu::create();	
    scene->addChild(layer);	
    return scene;
}

bool MainMenu::init()
{    
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm_menu.wav", true);
	
	auto mainMenuBackground = Sprite::create("background/MainMenuBackground.png");
	mainMenuBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mainMenuBackground, -50);

	// create the main menu items
	auto playButton = MenuItemImage::create("buttons/PlayNormal.png", "buttons/PlaySelected.png", CC_CALLBACK_1(MainMenu::playGame, this));
	playButton->setPosition(Point(visibleSize.width / 2, SCREEN_ORIGIN.y + (visibleSize.height / 10) * 2));
	auto highscoresButton = MenuItemImage::create("buttons/TrophyNormal.png", "buttons/TrophySelected.png", CC_CALLBACK_1(MainMenu::leaderboard, this));
	highscoresButton->setPosition(Point(visibleSize.width / 4, SCREEN_ORIGIN.y + (visibleSize.height / 10) * 2));
	auto settingsButton = MenuItemImage::create("buttons/settings2.png", "buttons/settings2.png", CC_CALLBACK_1(MainMenu::settings, this));
	settingsButton->setPosition(Point(visibleSize.width / 4 * 3, SCREEN_ORIGIN.y + (visibleSize.height / 10) * 2));

	// create menu and add menu items
	//auto* menu = Menu::create(playButton, highscoresButton, settingsButton, NULL);
	auto* menu = Menu::create(playButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	addParticlesToButtons(playButton);
	addParticlesToButtons(settingsButton);
	addParticlesToButtons(highscoresButton);
		
	// Settings
	popupSettings = Popup::createPopup();
	auto backButton = MenuItemImage::create("buttons/back.png", "buttons/back.png", CC_CALLBACK_1(MainMenu::back, this));	
	soundButton = MenuItemImage::create("buttons/soundON.png", "buttons/soundOFF.png", CC_CALLBACK_1(MainMenu::sound, this));
	WorldManager::getInstance()->setSoundEnabled(true);

	// Create menu and add menu items
	auto* menuSettings = Menu::create(soundButton, backButton, NULL);
	menuSettings->alignItemsVertically();
	popupSettings->addChild(menuSettings, 2);
	this->addChild(popupSettings, 1);	
	CCLOG("MainMenu initialized");
    return true;
}

void MainMenu::addParticlesToButtons(MenuItemImage* button)
{
	auto emitter = ParticleSystemQuad::create("particles/Flower.plist");
	emitter->setPosition(Point(button->getContentSize().width / 2, button->getContentSize().height / 2));
	emitter->setEmissionRate(200.00);
	emitter->setTotalParticles(50);
	emitter->setAutoRemoveOnFinish(true);
	button->addChild(emitter);
}

void MainMenu::playGame(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->resetGameWorld();
	CollisionManager::getInstance()->resetCollisionManager();
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);		
}

void MainMenu::leaderboard(cocos2d::Ref *pSender)
{	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}

void MainMenu::settings(cocos2d::Ref *pSender)
{		
	popupSettings->show(true, false);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}

void MainMenu::back(CCObject* pSender)
{
	popupSettings->show(false, false);	
}

void MainMenu::sound(CCObject* pSender)
{
	if (WorldManager::getInstance()->isSoundEnabled()){		
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();		
		WorldManager::getInstance()->setSoundEnabled(false);
	}
	else{		
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm_menu.wav", true);
		WorldManager::getInstance()->setSoundEnabled(true);
	}
	 
}

void MainMenu::mainMenuCleanup()
{
	CCLOG("Main menu cleanup");
}
