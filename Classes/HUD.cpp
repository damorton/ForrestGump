#include "HUD.h"
#include "WorldManager.h"
#include "Definitions.h"

bool HUD::init()
{	
	if (!Layer::init())
	{
		return false;
	}
	this->setColor(cocos2d::Color3B(0, 0, 0));
	this->setContentSize(cocos2d::Size::Size(1, 1));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Score
	auto distanceLabel = Label::createWithTTF("Distance ", LABEL_FONT, 32);
	this->addChild(distanceLabel);
	distanceLabel->setPosition(Vec2(PADDING + origin.x + distanceLabel->getContentSize().width / 2, origin.y + visibleSize.height - PADDING - distanceLabel->getContentSize().height / 2));
	distanceLabel->setColor(Color3B(0, 0, 0)); // black
	m_nDistance = 0;
	// Score label		
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(m_nDistance), VALUE_FONT, 32);
	this->addChild(m_pDistanceValueLabel);
	m_pDistanceValueLabel->setPosition(Vec2(PADDING * 5 + distanceLabel->getContentSize().width, distanceLabel->getPositionY()));
	m_pDistanceValueLabel->setColor(Color3B(0, 0, 0)); // black
		
	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, 32);
	this->addChild(coinsLabel);
	coinsLabel->setPosition(Vec2(PADDING + origin.x + coinsLabel->getContentSize().width / 2, distanceLabel->getPositionY() - PADDING * 2 - distanceLabel->getContentSize().height / 2));	
	coinsLabel->setColor(Color3B(0, 0, 0)); // black
	m_nCoins = 0;
	// Coins label		
	m_lCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), VALUE_FONT, 32);
	this->addChild(m_lCoinsValueLabel);
	m_lCoinsValueLabel->setPosition(Vec2(PADDING * 5 + distanceLabel->getContentSize().width, coinsLabel->getPositionY()));
	m_lCoinsValueLabel->setColor(Color3B(0, 0, 0)); // black

	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, 32);
	this->addChild(itemsLabel);
	itemsLabel->setPosition(Vec2(PADDING + origin.x + itemsLabel->getContentSize().width / 2, coinsLabel->getPositionY() - PADDING * 2 - coinsLabel->getContentSize().height / 2));
	itemsLabel->setColor(Color3B(0, 0, 0)); // black
	m_nItems = 0;
	// Items label		
	m_lItemsValueLabel = Label::createWithTTF(std::to_string(m_nItems), VALUE_FONT, 32);
	this->addChild(m_lItemsValueLabel);
	m_lItemsValueLabel->setPosition(Vec2(PADDING * 5 + distanceLabel->getContentSize().width, itemsLabel->getPositionY()));
	m_lItemsValueLabel->setColor(Color3B(0, 0, 0)); // black
	
	
	// Menu 
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(HUD::pauseGame, this));
	menu_item_pause->setPosition(Vec2(origin.x + visibleSize.width - menu_item_pause->getContentSize().width / 2,
		origin.y + visibleSize.height - menu_item_pause->getContentSize().height / 2));
		
	auto* hudButtonsMenu = Menu::create(menu_item_pause, NULL);
	hudButtonsMenu->setPosition(Point(0, 0));
	this->addChild(hudButtonsMenu);

	CCLOG("HUD initialized");
	return true;
}

void HUD::update()
{
	if (WorldManager::getInstance()->getPlayer() != NULL)
	{
		WorldManager::getInstance()->getPlayer()->addDistance();		
		m_pDistanceValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()));
		m_lCoinsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()));
		m_lItemsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()));
	}
}

void HUD::pauseGame(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->gameLayer()->pause();
}