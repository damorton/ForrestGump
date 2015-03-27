/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	HUD.cpp

	Description: HUD layer is responsible by UI (User Interface).
	Score and Distance are some feature controlled by HUD.
	Pause menu is on HUD.

*/

// Includes
#include "HUD.h"
#include "WorldManager.h"
#include "GameScene.h"
#include "Popup.h"
#include "Player.h"

// Init function that initialize the HUD class 
bool HUD::init()
{	
	if (!Layer::init())
	{
		return false;
	}

	m_nDistance = 0;
	m_nCoins = 0;
	m_nItems = 0;
	m_nBoosters = 0;
	m_nFood = 0;

	m_Size = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

	this->setColor(cocos2d::Color3B(0, 0, 0));
	this->setContentSize(cocos2d::Size::Size(1, 1));
	
	m_pPlayer = WorldManager::getInstance()->getPlayer();

	// Distance
	auto distanceLabel = Label::createWithTTF("Distance ", LABEL_FONT, LABEL_FONT_SIZE);
	distanceLabel->setPosition(Vec2(m_Origin.x + PADDING + distanceLabel->getContentSize().width / 2, m_Origin.y + VISIBLE_SIZE_HEIGHT - PADDING - distanceLabel->getContentSize().height / 2));
	distanceLabel->setColor(Color3B(255, 255, 255));
	distanceLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(distanceLabel);
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(m_nDistance) + "m", LABEL_FONT, LABEL_FONT_SIZE);
	//m_pDistanceValueLabel->setPosition(Vec2(distanceLabel->getPositionX() + distanceLabel->getContentSize().width / 2 + PADDING + m_pDistanceValueLabel->getContentSize().width/2, distanceLabel->getPositionY()));
	m_pDistanceValueLabel->setPosition(Vec2((m_Size.width / 3.5) - PADDING - m_pDistanceValueLabel->getContentSize().width / 2, distanceLabel->getPositionY()));	
	m_pDistanceValueLabel->setColor(Color3B(DISTANCE_VALUE_LABEL_COLOR));
	m_pDistanceValueLabel->enableOutline(Color4B(255, 255, 255, 255));
	m_pDistanceValueLabel->enableGlow(Color4B(255, 255, 255, 255));
	this->addChild(m_pDistanceValueLabel);
	
	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);
	coinsLabel->setPosition(Vec2(m_Origin.x + PADDING + coinsLabel->getContentSize().width / 2, distanceLabel->getPositionY() - PADDING - distanceLabel->getContentSize().height / 2));
	coinsLabel->setColor(Color3B(255, 255, 255));
	coinsLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(coinsLabel);
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), LABEL_FONT, LABEL_FONT_SIZE);
	//m_pCoinsValueLabel->setPosition(Vec2(coinsLabel->getPositionX() + coinsLabel->getContentSize().width / 2 + PADDING + m_pCoinsValueLabel->getContentSize().width / 2, coinsLabel->getPositionY()));
	m_pCoinsValueLabel->setPosition(Vec2((m_Size.width / 3.5) - PADDING - m_pCoinsValueLabel->getContentSize().width / 2, coinsLabel->getPositionY()));
	m_pCoinsValueLabel->setColor(Color3B(255, 255, 64));
	m_pCoinsValueLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(m_pCoinsValueLabel);
		
	// Menu 
	menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(HUD::pause, this));
	menu_item_pause->setPosition(Vec2(m_Origin.x + VISIBLE_SIZE_WIDTH - menu_item_pause->getContentSize().width / 2,
		m_Origin.y + VISIBLE_SIZE_HEIGHT - menu_item_pause->getContentSize().height / 2));
		
	auto* hudButtonsMenu = Menu::create(menu_item_pause, NULL);
	hudButtonsMenu->setPosition(Point(0, 0));
	this->addChild(hudButtonsMenu);

	
	// Add Pause menu to HUD
	popup = Popup::createPopup();
	

	// Add botoes
	// Buttons
	auto resumeButton = MenuItemImage::create("buttons/btNotResumeGame.png", "buttons/btActResumeGame.png", CC_CALLBACK_1(HUD::resume, this));
	auto mainMenuButton = MenuItemImage::create("buttons/btNotMainGame.png", "buttons/btActMainGame.png", CC_CALLBACK_1(HUD::mainMenu, this));

	// Create menu and add menu items
	auto* menu = Menu::create(resumeButton, mainMenuButton, NULL);
	menu->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);
	menu->alignItemsVertically();
	
	// Add botoes to pop menu
	popup->addChild(menu, 2);
	// Add pop menu to HUD Layer
	this->addChild(popup, 1);
	
	return true;
}

// Initiallizing label with value (Score, Distance)
void HUD::initLabelWithValue(Label* label, Vec2 position, Label* value)
{	
	this->addChild(label);
	this->addChild(value);
	label->setPosition(position);
	label->setColor(Color3B(200, 0, 0));
	label->enableOutline(Color4B(0,0,0,255));
	label->enableGlow(Color4B(255, 255, 51, 255));	
	value->setPosition(Vec2(label->getPositionX() + label->getContentSize().width / 2 + PADDING, label->getPositionY()));
	value->setColor(Color3B(0, 0, 0));
	value->enableGlow(Color4B(255, 255, 51, 255));
}

// Update method
void HUD::update()
{
	if (m_pPlayer != NULL)
	{
		m_pDistanceValueLabel->setString(std::to_string(m_pPlayer->getDistance()) + "m");
		m_pCoinsValueLabel->setString(std::to_string(m_pPlayer->getCoins()));
	}
}

// Pause game
void HUD::pause(CCObject* pSender)
{
	this->togglePause(true);
}

// Resume game
void HUD::resume(CCObject* pSender)
{
	this->togglePause(false);
}

// Back to MainMenu scene
void HUD::mainMenu(CCObject* pSender)
{
	// Unpause the director	
	WorldManager::getInstance()->gameLayer()->mainMenu();		
}

// Switch between game paused or not
void HUD::togglePause(bool paused)
{
	popup->show(paused, true);
	menu_item_pause->setVisible(!paused);

	// Set game layer touch enabled
	//WorldManager::getInstance()->gameLayer()->setTouchEnabled(!paused);
	WorldManager::getInstance()->gameLayer()->pauseGame();
}

// TODO : Implement clean up function 
void HUD::hudCleanup()
{
	//CCLOG("HUD Cleanup");
}