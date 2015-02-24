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
	playAgainButton->setPosition(Point((m_Size.width * 0.75), m_Origin.y + PADDING + playAgainButton->getContentSize().height / 2));

	// create menu and add menu items
	//auto* menu = Menu::create(resumeButton, mainMenuButton, exitButton, NULL);
	auto* menu = Menu::create(playAgainButton, NULL);
	menu->setPosition(Vec2::ZERO);

	this->displayPlayerStatistics();
	this->addChild(menu);
	
	return success;
}

void GameOver::displayPlayerStatistics()
{
	// Distance
	auto distanceLabel = Label::createWithTTF(WorldManager::getInstance()->getPlayerUsername() + " YOU RAN", LABEL_FONT, LABEL_FONT_SIZE* 1.5);
	distanceLabel->setPosition(Vec2((m_Size.width * 0.25), m_Origin.y + (VISIBLE_SIZE_HEIGHT / 4 )*3 - distanceLabel->getContentSize().height / 2));
	distanceLabel->setColor(Color3B(255, 255, 255));
	distanceLabel->enableGlow(Color4B(255, 255, 51, 255));
	distanceLabel->setRotation(-6.0f);
	this->addChild(distanceLabel);
	auto distanceValue = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()) + "m", LABEL_FONT, LABEL_FONT_SIZE * 4);
	distanceValue->setPosition(Vec2(distanceLabel->getPositionX(), distanceLabel->getPositionY() - PADDING - distanceValue->getContentSize().height / 2));
	distanceValue->setColor(Color3B(255, 255, 64));
	distanceValue->enableGlow(Color4B(255, 255, 51, 255));
	distanceValue->setRotation(-6.0f);
	this->addChild(distanceValue);
	
	auto newHighscore = Label::createWithTTF("NEW HIGHSCORE!", LABEL_FONT, LABEL_FONT_SIZE);
	newHighscore->setPosition(Vec2(distanceLabel->getPositionX(), distanceValue->getPositionY() - PADDING - distanceValue->getContentSize().height / 2 - newHighscore->getContentSize().height / 2));
	newHighscore->setColor(Color3B(255, 0, 0));
	newHighscore->enableGlow(Color4B(255, 255, 51, 255));
	newHighscore->setRotation(-6.0f);
	newHighscore->setVisible(false);
	this->addChild(newHighscore);

	int previousHighscore = std::atoi(WorldManager::getInstance()->getPlayerHighscore().c_str());
	CCLOG("previous %d", previousHighscore);
	int currentScore = WorldManager::getInstance()->getPlayer()->getDistance();
	CCLOG("current %d", currentScore);
	if (currentScore > previousHighscore)
	{
		CCLOG("New higscore recorded!");
		newHighscore->setVisible(true);
		auto scaleUp = ScaleBy::create(.5, 2.0);
		auto scaleDown = ScaleBy::create(.5, 0.5);
		auto scaling = Sequence::create(scaleUp, scaleDown, NULL);
		newHighscore->runAction(scaling);
		this->storeHighscore();
	}
		
	auto statsLabel = Label::createWithTTF("STATISTICS", LABEL_FONT, LABEL_FONT_SIZE * 1.5);	
	statsLabel->setPosition(Point((m_Size.width * 0.75), m_Origin.y + m_Size.height - PADDING - statsLabel->getContentSize().height / 2));
	statsLabel->setColor(Color3B(255, 255, 255));
	statsLabel->enableOutline(Color4B(0, 0, 0, 255));
	statsLabel->enableGlow(Color4B(0, 0, 0, 255));
	this->addChild(statsLabel);

	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);		
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(coinsLabel, m_pCoinsValueLabel, statsLabel);
	
	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pItemsValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getItems()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(itemsLabel, m_pItemsValueLabel, coinsLabel);


	// Boosters
	auto boostersLabel = Label::createWithTTF("Boosters ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pBoostersValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getBoosters()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(boostersLabel, m_pBoostersValueLabel, itemsLabel);

	// Food
	auto foodLabel = Label::createWithTTF("Food ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pFoodValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getFood()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(foodLabel, m_pFoodValueLabel, boostersLabel);

	// Duration of session
	// Number of jumps
	// Time on foot
	// Time jumping
	// Enemies dodged
	// Enemies killed	
}

void GameOver::initLabelWithValue(Label* label, Label* value, Label* labelAbove)
{	
	label->setPosition(Vec2((m_Size.width / 2) + PADDING + label->getContentSize().width / 2, labelAbove->getPositionY() - labelAbove->getContentSize().height / 2));
	label->setColor(Color3B(200, 200, 200));
	label->enableOutline(Color4B(0, 0, 0, 255));
	label->enableGlow(Color4B(0, 0, 0, 255));
	this->addChild(label);
	value->setPosition(Vec2(m_Size.width - PADDING - value->getContentSize().width / 2, label->getPositionY()));
	value->setColor(Color3B(200, 200, 200));
	value->enableOutline(Color4B(0, 0, 0, 255));
	value->enableGlow(Color4B(0, 0, 0, 255));
	this->addChild(value);
}

void GameOver::storeHighscore()
{
	WorldManager::getInstance()->setPlayerHighscore(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()));
}

void GameOver::displayLeaderboard()
{	
	std::shared_ptr<std::vector<User>> users = WorldManager::getInstance()->getDAO()->read();
	for (int i = 0; i < users->size(); i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}
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

