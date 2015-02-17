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
	m_nBoosters = 0;
	m_nFood = 0;

	m_Size = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

	this->setColor(cocos2d::Color3B(0, 0, 0));
	this->setContentSize(cocos2d::Size::Size(1, 1));
	
	// Distance
	auto distanceLabel = Label::createWithTTF("Distance ", LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabel(distanceLabel, Vec2(m_Origin.x + PADDING + distanceLabel->getContentSize().width / 2, m_Origin.y + VISIBLE_SIZE_HEIGHT - PADDING - distanceLabel->getContentSize().height / 2));
	m_fValuePosX = distanceLabel->getPositionX() + distanceLabel->getContentSize().width * .75;
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(m_nDistance), VALUE_FONT, LABEL_FONT_SIZE);
	this->initValueLabel(distanceLabel, m_pDistanceValueLabel);	
		
	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabel(coinsLabel, Vec2(m_Origin.x + PADDING + coinsLabel->getContentSize().width / 2, distanceLabel->getPositionY() - PADDING - coinsLabel->getContentSize().height / 2));
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), VALUE_FONT, LABEL_FONT_SIZE);
	this->initValueLabel(coinsLabel, m_pCoinsValueLabel);

	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabel(itemsLabel, Vec2(m_Origin.x + PADDING + itemsLabel->getContentSize().width / 2, coinsLabel->getPositionY() - PADDING - itemsLabel->getContentSize().height / 2));
	m_pItemsValueLabel = Label::createWithTTF(std::to_string(m_nItems), VALUE_FONT, LABEL_FONT_SIZE);
	this->initValueLabel(itemsLabel, m_pItemsValueLabel);
	
	// Boosters
	auto boostersLabel = Label::createWithTTF("Boosters ", LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabel(boostersLabel, Vec2(m_Origin.x + PADDING + boostersLabel->getContentSize().width / 2, itemsLabel->getPositionY() - PADDING - boostersLabel->getContentSize().height / 2));
	m_pBoostersValueLabel = Label::createWithTTF(std::to_string(m_nBoosters), VALUE_FONT, LABEL_FONT_SIZE);
	this->initValueLabel(boostersLabel, m_pBoostersValueLabel);

	// Food
	auto foodLabel = Label::createWithTTF("Food ", LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabel(foodLabel, Vec2(m_Origin.x + PADDING + foodLabel->getContentSize().width / 2, boostersLabel->getPositionY() - PADDING - foodLabel->getContentSize().height / 2));
	m_pFoodValueLabel = Label::createWithTTF(std::to_string(m_nFood), VALUE_FONT, LABEL_FONT_SIZE);
	this->initValueLabel(foodLabel, m_pFoodValueLabel);

	// Menu 
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(HUD::pauseGame, this));
	menu_item_pause->setPosition(Vec2(m_Origin.x + VISIBLE_SIZE_WIDTH - menu_item_pause->getContentSize().width / 2,
		m_Origin.y + VISIBLE_SIZE_HEIGHT - menu_item_pause->getContentSize().height / 2));
		
	auto* hudButtonsMenu = Menu::create(menu_item_pause, NULL);
	hudButtonsMenu->setPosition(Point(0, 0));
	this->addChild(hudButtonsMenu);

	CCLOG("HUD initialized");
	return true;
}

void HUD::initLabel(Label* label, Vec2 position)
{	
	this->addChild(label);
	label->setPosition(position);
	label->setColor(Color3B(0, 0, 0)); // black
	label->enableGlow(Color4B(255, 255, 51, 255));
}

void HUD::initValueLabel(Label* label, Label* value)
{	
	this->addChild(value);
	value->setPosition(Vec2(m_fValuePosX, label->getPositionY()));
	value->setColor(Color3B(0, 0, 0)); // black	
	value->enableGlow(Color4B(255, 255, 51, 255));
}

void HUD::update()
{
	if (WorldManager::getInstance()->getPlayer() != NULL)
	{
		WorldManager::getInstance()->getPlayer()->addDistance();		
		m_pDistanceValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()));
		m_pCoinsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()));
		m_pItemsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getItems()));
		m_pBoostersValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getBoosters()));
		m_pFoodValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getFood()));
	}
}

void HUD::pauseGame(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->gameLayer()->pause();
}