/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

MainMenu.h

Description: Main menu placed at the beginning of the game.
It allows the user to play the game.

*/

#include "audio/include/SimpleAudioEngine.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "Popup.h"

// Create the Main Menu Scene
Scene* MainMenu::createScene()
{
    auto scene = Scene::create();    
    auto layer = MainMenu::create();	
    scene->addChild(layer);	
    return scene;
}

// Main Menu Initialization 
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

	// Create the main menu items
	m_pPlayButton = MenuItemImage::create("buttons/PlayNormal.png", "buttons/PlaySelected.png", CC_CALLBACK_1(MainMenu::playGame, this));
	m_pPlayButton->setPosition(Point(visibleSize.width / 2, SCREEN_ORIGIN.y + (visibleSize.height / 10) * 2));

	// Create menu and add menu items
	auto* menu = Menu::create(m_pPlayButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	addParticlesToButtons(m_pPlayButton);	

	WorldManager::getInstance()->setSoundEnabled(true);

	// Register Touch Event
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (!WorldManager::getInstance()->isXMLFileExist())
	{
		// TextField
		createTF();
		m_pPlayButton->setVisible(false);
	}
	
	//CCLOG("MainMenu initialized");
    return true;
}

// Adding effects to the Play Button 
void MainMenu::addParticlesToButtons(MenuItemImage* button)
{
	auto emitter = ParticleSystemQuad::create("particles/Flower.plist");
	emitter->setPosition(Point(button->getContentSize().width / 2, button->getContentSize().height / 2));
	emitter->setEmissionRate(200.00);
	emitter->setTotalParticles(50);
	emitter->setAutoRemoveOnFinish(true);
	button->addChild(emitter);
}

// Call the Game Scene
void MainMenu::playGame(cocos2d::Ref *pSender)
{		
	if (!WorldManager::getInstance()->isXMLFileExist())
	{			
		WorldManager::getInstance()->setUsername(m_pTextField->getString());			
	}	
	WorldManager::getInstance()->createDAO();
	WorldManager::getInstance()->resetGameWorld();
	CollisionManager::getInstance()->resetCollisionManager();
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);		
}

// TODO : Clean up function */
void MainMenu::mainMenuCleanup()
{
	//CCLOG("Main menu cleanup");
}

// Getting the user name to save score
void MainMenu::createTF()
{
	m_pTextField = TextFieldTTF::textFieldWithPlaceHolder("ENTER USERNAME", LABEL_FONT_ROBOTO, LABEL_FONT_SIZE);
	m_pTextField->setColor(Color3B::RED);	
	m_pTextField->setColorSpaceHolder(Color3B::RED);

	m_nCharLimit = 12;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)    
	// On android, TextFieldTTF cannot auto adjust its position when soft-keyboard pop up
	// So we had to set a higher position
	m_pTextField->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2 + 50));
#else
	m_pTextField->setPosition(Vec2(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT * .90));
#endif	
	m_pTextField->setDelegate(this);
	m_pTextField->attachWithIME();
	this->addChild(m_pTextField);	
}

// Allow touches on screen
bool MainMenu::onTouchBegan(Touch *pTouch, Event *pEvent)
{
	return true;
}

bool MainMenu::onTextFieldAttachWithIME(TextFieldTTF * pSender)
{
	return false;
}

bool MainMenu::onTextFieldDetachWithIME(TextFieldTTF * pSender)
{
	return false;
}

// Create a field to input user details
bool MainMenu::onTextFieldInsertText(TextFieldTTF *pSender, const char *text, size_t nLen)
{	
	// Do not allow the user to enter incorrect characters into username 
	if (' ' == *text || '\n' == *text)
	{
		CCLOG("Incorrect character entered into username");
		return true;
	}	

	// If the textfield's char count more than _charLimit, doesn't insert text anymore.
	if (pSender->getCharCount() >= m_nCharLimit)
	{
		return true;
	}
		
	// Create a insert text sprite and do some action to add an effect
	auto label = Label::createWithSystemFont(text, LABEL_FONT_ROBOTO, LABEL_FONT_SIZE);
	this->addChild(label);	
	label->setColor(Color3B::YELLOW);

	// Move the sprite from top to position
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
	CCLOG("Username character count : %d", m_pTextField->getCharCount());
	// Check username
	if (m_pTextField->getCharCount() >= 3) m_pPlayButton->setVisible(true);
	return false;
}

void MainMenu::callbackRemoveNodeWhenDidAction(Node * node)
{
	this->removeChild(node, true);
}

bool MainMenu::onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, size_t nLen)
{		
	// Create a delete text sprite and do some action
	auto label = Label::createWithSystemFont(delText, LABEL_FONT_ROBOTO, LABEL_FONT_SIZE);
	this->addChild(label);

	// Move the sprite to fly out
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

	CCLOG("Username character count : %d", m_pTextField->getCharCount());
	if (m_pTextField->getCharCount() <= 4) m_pPlayButton->setVisible(false);

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
