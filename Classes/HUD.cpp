#include "HUD.h"
#include "WorldManager.h"
#include "Definitions.h"

bool HUD::init()
{	
	if (!Layer::init())
	{
		return false;
	}

	m_nDistance = 0;
	m_nCoins = 0;
	m_nItems = 0;

	this->setColor(cocos2d::Color3B(0, 0, 0));
	this->setContentSize(cocos2d::Size::Size(1, 1));
	
	// Score
	auto distanceLabel = Label::createWithTTF("Distance ", LABEL_FONT, 32);
	this->initLabel(distanceLabel);	
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(m_nDistance), VALUE_FONT, 32);
	this->initValueLabel(m_pDistanceValueLabel);
		
	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, 32);
	this->initLabel(coinsLabel);	
	m_lCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), VALUE_FONT, 32);
	this->initValueLabel(m_lCoinsValueLabel);

	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, 32);
	this->initLabel(itemsLabel);	
	m_lItemsValueLabel = Label::createWithTTF(std::to_string(m_nItems), VALUE_FONT, 32);
	this->initValueLabel(m_lItemsValueLabel);
	

	// Menu 
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(HUD::pauseGame, this));
	menu_item_pause->setPosition(Vec2(ORIGIN.x + VISIBLE_SIZE_WIDTH - menu_item_pause->getContentSize().width / 2,
		ORIGIN.y + VISIBLE_SIZE_HEIGHT - menu_item_pause->getContentSize().height / 2));
		
	auto* hudButtonsMenu = Menu::create(menu_item_pause, NULL);
	hudButtonsMenu->setPosition(Point(0, 0));
	this->addChild(hudButtonsMenu);

	CCLOG("HUD initialized");
	return true;
}

void HUD::initLabel(Label* label)
{
	this->addChild(label);
	label->setPosition(Vec2(ORIGIN.x + PADDING + label->getContentSize().width / 2, ORIGIN.y + VISIBLE_SIZE_HEIGHT - PADDING - label->getContentSize().height / 2));
	label->setColor(Color3B(0, 0, 0)); // black
}

void HUD::initValueLabel(Label* label)
{
	this->addChild(m_pDistanceValueLabel);
	m_pDistanceValueLabel->setPosition(Vec2(PADDING * 5 + label->getContentSize().width, label->getPositionY()));
	m_pDistanceValueLabel->setColor(Color3B(0, 0, 0)); // black
}

void HUD::update()
{
	if (WorldManager::getInstance()->getPlayer() != NULL)
	{
		WorldManager::getInstance()->getPlayer()->addDistance();		
		m_pDistanceValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()));
		m_lCoinsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()));
		m_lItemsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getItems()));
	}
}

void HUD::pauseGame(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->gameLayer()->pause();
}