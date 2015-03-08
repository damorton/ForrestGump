#include "MainMenu.h"
#include "GameScene.h"

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
	auto highscoresButton = MenuItemImage::create("buttons/TrophyNormal.png", "buttons/TrophySelected.png", CC_CALLBACK_1(MainMenu::leaderboard, this));
	auto settingsButton = MenuItemImage::create("buttons/settings2.png", "buttons/settings2.png", CC_CALLBACK_1(MainMenu::settings, this));


	// creation of actions for tweening of main menu
	auto ccPlayBtnAction = MoveBy::create(1, Point(visibleSize.width / 2, (visibleSize.height / 8) * 2));
	playButton->runAction(ccPlayBtnAction);
	

	auto ccSettingsBtnAction = MoveBy::create(1, Point(visibleSize.width / 4, (visibleSize.height / 5) * 2));
	settingsButton->runAction(ccSettingsBtnAction);

	auto ccHighScoreBtnAction = MoveBy::create(1, Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 2));
	highscoresButton->runAction(ccHighScoreBtnAction);

	// loading .plist file
	//CCString* file = CCString::create("sprites/walk.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(file->getCString());
	
	auto rotateAction = RotateBy::create(2.0f, 360.0f);
	playButton->runAction(rotateAction);
	
	auto rotateAction2 = RotateBy::create(2.0f, 360.0f);
	settingsButton->runAction(rotateAction2);

	auto rotateAction3 = RotateBy::create(2.0f, 360.0f);
	highscoresButton->runAction(rotateAction3);

	// create menu and add menu items
	auto* menu = Menu::create(playButton, highscoresButton, settingsButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	// particle testing  for high scores button
	CCParticleSystem *ccEmitter = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter->setPosition(Point(highscoresButton->getContentSize().width / 2, highscoresButton->getContentSize().height / 2));
	ccEmitter->setEmissionRate(200.00);
	ccEmitter->setTotalParticles(50);
	//this->addChild(ccEmitter);

	// particle testing for play button
	CCParticleSystem *ccEmitter2 = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter2->setPosition(Point(playButton->getContentSize().width / 2, playButton->getContentSize().height / 2));
	ccEmitter2->setEmissionRate(300.00);
	ccEmitter2->setTotalParticles(50);
	//this->addChild(ccEmitter2);

	// particle testing for settings button
	CCParticleSystem *ccEmitter3 = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter3->setPosition(Point(settingsButton->getContentSize().width / 2, settingsButton->getContentSize().height / 2));
	ccEmitter3->setEmissionRate(300.00);
	ccEmitter3->setTotalParticles(50);
	//this->addChild(ccEmitter3);

	playButton->addChild(ccEmitter2);
	settingsButton->addChild(ccEmitter3);
	highscoresButton->addChild(ccEmitter);

	/*
	// Settings

	// Add Pause menu to HUD
	popupSettings = Popup::createPopup();


	// Add botoes
	// Buttons
	auto backButton = MenuItemImage::create("buttons/btNotBack.png", "buttons/btBack.png", CC_CALLBACK_1(MainMenu::back, this));

	// create menu and add menu items
	auto* menu = Menu::create(backButton, NULL);
	menu->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);
	menu->alignItemsVertically();

	// Add botoes to pop menu
	popupSettings->addChild(menu, 2);
	// Add pop menu to HUD Layer
	this->addChild(popupSettings, 1);	
	*/
    return true;
}

void MainMenu::mainMenu()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenu::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);		
}

void MainMenu::playGame(cocos2d::Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
	
}

void MainMenu::leaderboard(cocos2d::Ref *pSender)
{	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	
}

void MainMenu::settings(cocos2d::Ref *pSender)
{		

//	popupSettings->show(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);	

}
/*
void MainMenu::back(CCObject* pSender)
{
	popupSettings->show(false);	
}
*/
