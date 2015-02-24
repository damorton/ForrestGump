#include "GameOver.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{    
    if ( !Layer::init() )
    {
        return false;
    }    
	this->initializeGameOverScene();
    return true;
}

bool GameOver::initializeGameOverScene()
{
	bool success = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm_menu.wav", true);

	m_Size = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

	m_nDistance = 56754;
	m_nCoins = 234;
	m_nItems = 23;
	m_nBoosters = 6;
	m_nFood = 8906;

	auto gameOverBackground = Sprite::create("background/GameOverBackground.png");
	gameOverBackground->setPosition(Vec2(m_Size.width / 2 + m_Origin.x, m_Size.height / 2 + m_Origin.y));
	this->addChild(gameOverBackground, -50);

	// create the GameOver menu items
	//auto resumeButton = MenuItemImage::create("buttons/resume.png", "buttons/resume_clicked.png", CC_CALLBACK_1(GameOver::resume, this));
	//auto mainMenuButton = MenuItemImage::create("buttons/menu.png", "buttons/menu_clicked.png", CC_CALLBACK_1(GameOver::mainMenu, this));
	//auto exitButton = MenuItemImage::create("buttons/exit.png", "buttons/exit_clicked.png", CC_CALLBACK_1(GameOver::exit, this));

	auto playAgainButton = MenuItemImage::create("buttons/PlayAgainNormal.png", "buttons/PlayAgainClicked.png", CC_CALLBACK_1(GameOver::playAgain, this));

	// position the menu buttons on screen
	//resumeButton->setPosition(Point(m_Size.width / 2, (m_Size.height / 3) + 150));
	//mainMenuButton->setPosition(Point(m_Size.width / 2, (m_Size.height / 3)));
	//exitButton->setPosition(Point(m_Size.width - 50, (m_Size.height / 3)-100));
	playAgainButton->setPosition(Point(m_Size.width / 2, m_Size.height / 4 * 1));

	// create menu and add menu items
	//auto* menu = Menu::create(resumeButton, mainMenuButton, exitButton, NULL);
	auto* menu = Menu::create(playAgainButton, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addStatistics();
	this->addChild(menu);
	
	return success;
}

void GameOver::addStatistics()
{
	// Distance
	auto distanceLabel = Label::createWithTTF(WorldManager::getInstance()->getPlayerUsername() + " YOU RAN", LABEL_FONT, LABEL_FONT_SIZE);
	distanceLabel->setPosition(Vec2((m_Size.width * 0.25), m_Origin.y + (VISIBLE_SIZE_HEIGHT / 4 )*3 - distanceLabel->getContentSize().height / 2));
	distanceLabel->setColor(Color3B(255, 255, 255));
	distanceLabel->enableOutline(Color4B(0, 0, 0, 255));
	distanceLabel->enableGlow(Color4B(255, 255, 51, 255));
	distanceLabel->setRotation(-6.0f);
	this->addChild(distanceLabel);

	m_pDistanceValueLabel = Label::createWithTTF(WorldManager::getInstance()->getPlayerDistanceScore() + "m", VALUE_FONT, LABEL_FONT_SIZE*3);
	m_pDistanceValueLabel->setPosition(Vec2(distanceLabel->getPositionX(), distanceLabel->getPositionY() - PADDING - m_pDistanceValueLabel->getContentSize().height / 2));
	m_pDistanceValueLabel->setColor(Color3B(255, 255, 64));
	m_pDistanceValueLabel->enableGlow(Color4B(255, 255, 51, 255));
	m_pDistanceValueLabel->setRotation(-6.0f);
	this->addChild(m_pDistanceValueLabel);

	// statistcis png for title?
	// set all labels relative to the statistics png image

	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(coinsLabel,
		Vec2((m_Size.width / 2) + PADDING + coinsLabel->getContentSize().width / 2, m_Origin.y + VISIBLE_SIZE_HEIGHT - PADDING - coinsLabel->getContentSize().height / 2),
		m_pCoinsValueLabel);

	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pItemsValueLabel = Label::createWithTTF(std::to_string(m_nItems), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(itemsLabel,
		Vec2((m_Size.width / 2) + PADDING + itemsLabel->getContentSize().width / 2, coinsLabel->getPositionY() - PADDING - itemsLabel->getContentSize().height / 2),
		m_pItemsValueLabel);

	// Boosters
	auto boostersLabel = Label::createWithTTF("Boosters ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pBoostersValueLabel = Label::createWithTTF(std::to_string(m_nBoosters), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(boostersLabel,
		Vec2((m_Size.width / 2) + PADDING + boostersLabel->getContentSize().width / 2, itemsLabel->getPositionY() - PADDING - boostersLabel->getContentSize().height / 2),
		m_pBoostersValueLabel);

	// Food
	auto foodLabel = Label::createWithTTF("Food ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pFoodValueLabel = Label::createWithTTF(std::to_string(m_nFood), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(foodLabel,
		Vec2((m_Size.width / 2) + PADDING + foodLabel->getContentSize().width / 2, boostersLabel->getPositionY() - PADDING - foodLabel->getContentSize().height / 2),
		m_pFoodValueLabel);
}

void GameOver::initLabelWithValue(Label* label, Vec2 position, Label* value)
{
	this->addChild(label);
	this->addChild(value);
	label->setPosition(position);
	label->setColor(Color3B(64, 64, 64));
	label->enableOutline(Color4B(0, 0, 0, 255));
	label->enableGlow(Color4B(255, 255, 51, 255));
	value->setPosition(Vec2(m_Size.width - PADDING - value->getContentSize().width / 2, label->getPositionY()));
	value->setColor(Color3B(64, 64, 64));
	value->enableGlow(Color4B(255, 255, 51, 255));
}

void GameOver::playAgain(cocos2d::Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);
}

void GameOver::resume(cocos2d::Ref *pSender)
{
    Director::getInstance()->popScene();		
}

void GameOver::mainMenu(cocos2d::Ref *pSender)
{
	Director::getInstance()->popScene();
    auto scene = MainMenu::createScene();    
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}

void GameOver::exit(cocos2d::Ref *pSender)
{
	Director::getInstance()->end();
}

