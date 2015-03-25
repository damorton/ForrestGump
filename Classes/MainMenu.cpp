#include "MainMenu.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "audio/include/SimpleAudioEngine.h"

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

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (!WorldManager::getInstance()->isXMLFileExist())
	{
		// TextField
		createTF();
	}

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
	if (!WorldManager::getInstance()->isXMLFileExist())
	{
		WorldManager::getInstance()->setUsername(m_pTextField->getString());
		WorldManager::getInstance()->addUser(m_pTextField->getString());
	}
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

void MainMenu::createTF()
{
	m_pTextField = TextFieldTTF::textFieldWithPlaceHolder("ENTER USERNAME", LABEL_FONT, LABEL_FONT_SIZE);	
	m_pTextField->setColor(Color3B::MAGENTA);	
	m_nCharLimit = 12;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)    
	// on android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
	// so we had to set a higher position
	m_pTextField->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2 + 50));
#else
	m_pTextField->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT * .90));
#endif	
	m_pTextField->setDelegate(this);
	m_pTextField->attachWithIME();
	this->addChild(m_pTextField);	
}

bool MainMenu::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	m_beginPos = pTouch->getLocation();
	return true;
}

void MainMenu::onTouchEnded(Touch *pTouch, Event *pEvent)
{
	
}


bool MainMenu::onTextFieldAttachWithIME(TextFieldTTF * pSender)
{

	return false;

}

bool MainMenu::onTextFieldDetachWithIME(TextFieldTTF * pSender)
{
	return false;
}

bool MainMenu::onTextFieldInsertText(TextFieldTTF *pSender, const char *text, size_t nLen)
{	
	// if insert enter, treat as default to detach with ime
	if ('\n' == *text)
	{
		CCLOG("Enter hit");
		return false;
	}

	// if the textfield's char count more than _charLimit, doesn't insert text anymore.
	if (pSender->getCharCount() >= m_nCharLimit)
	{
		return true;
	}

	// create a insert text sprite and do some action
	auto label = Label::createWithSystemFont(text, LABEL_FONT, LABEL_FONT_SIZE);
	this->addChild(label);
	Color3B color(226, 121, 7);
	label->setColor(color);

	// move the sprite from top to position
	auto endPos = pSender->getPosition();
	if (pSender->getCharCount())
	{
		endPos.x += pSender->getContentSize().width / 2;
	}
	auto inputTextSize = label->getContentSize();
	Vec2 beginPos(endPos.x, Director::getInstance()->getWinSize().height - inputTextSize.height * 2);

	float duration = 0.5;
	label->setPosition(beginPos);
	label->setScale(8);

	auto seq = Sequence::create(
		Spawn::create(
		MoveTo::create(duration, endPos),
		ScaleTo::create(duration, 1),
		FadeOut::create(duration),
		nullptr),
		CallFuncN::create(CC_CALLBACK_1(MainMenu::callbackRemoveNodeWhenDidAction, this)),
		nullptr);
	label->runAction(seq);
	return false;
}

void MainMenu::callbackRemoveNodeWhenDidAction(Node * node)
{
	this->removeChild(node, true);
}

bool MainMenu::onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, size_t nLen)
{
	// create a delete text sprite and do some action
	auto label = Label::createWithSystemFont(delText, LABEL_FONT, LABEL_FONT_SIZE);
	this->addChild(label);

	// move the sprite to fly out
	auto beginPos = pSender->getPosition();
	auto textfieldSize = pSender->getContentSize();
	auto labelSize = label->getContentSize();
	beginPos.x += (textfieldSize.width - labelSize.width) / 2.0f;

	auto winSize = Director::getInstance()->getWinSize();
	Vec2 endPos(-winSize.width / 4.0f, winSize.height * (0.5 + (float)rand() / (2.0f * RAND_MAX)));

	float duration = 1;
	float rotateDuration = 0.2f;
	int repeatTime = 5;
	label->setPosition(beginPos);

	auto seq = Sequence::create(
		Spawn::create(
		MoveTo::create(duration, endPos),
		Repeat::create(
		RotateBy::create(rotateDuration, (rand() % 2) ? 360 : -360),
		repeatTime),
		FadeOut::create(duration),
		nullptr),
		CallFuncN::create(CC_CALLBACK_1(MainMenu::callbackRemoveNodeWhenDidAction, this)),
		nullptr);
	label->runAction(seq);
	return false;
}

bool MainMenu::onDraw(TextFieldTTF * pSender)
{
	return false;
}

static Rect getRect(Node * node)
{
	Rect rc;
	rc.origin = node->getPosition();
	rc.size = node->getContentSize();
	rc.origin.x -= rc.size.width / 2;
	rc.origin.y -= rc.size.height / 2;
	return rc;
}

void MainMenu::keyboardWillShow(IMEKeyboardNotificationInfo &info)
{
	
}

void MainMenu::keyboardWillHide(IMEKeyboardNotificationInfo &info)
{
	
}
