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
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(m_nDistance), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(distanceLabel,
		Vec2(m_Origin.x + PADDING + distanceLabel->getContentSize().width / 2, m_Origin.y + VISIBLE_SIZE_HEIGHT - PADDING - distanceLabel->getContentSize().height / 2),
		m_pDistanceValueLabel);
			
	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(coinsLabel,
		Vec2(m_Origin.x + PADDING + coinsLabel->getContentSize().width / 2, distanceLabel->getPositionY() - PADDING - coinsLabel->getContentSize().height / 2),
		m_pCoinsValueLabel);
	
	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pItemsValueLabel = Label::createWithTTF(std::to_string(m_nItems), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(itemsLabel,
		Vec2(m_Origin.x + PADDING + itemsLabel->getContentSize().width / 2, coinsLabel->getPositionY() - PADDING - itemsLabel->getContentSize().height / 2),
		m_pItemsValueLabel);
		
	// Boosters
	auto boostersLabel = Label::createWithTTF("Boosters ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pBoostersValueLabel = Label::createWithTTF(std::to_string(m_nBoosters), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(boostersLabel,
		Vec2(m_Origin.x + PADDING + boostersLabel->getContentSize().width / 2, itemsLabel->getPositionY() - PADDING - boostersLabel->getContentSize().height / 2),
		m_pBoostersValueLabel);	

	// Food
	auto foodLabel = Label::createWithTTF("Food ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pFoodValueLabel = Label::createWithTTF(std::to_string(m_nFood), VALUE_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(foodLabel,
		Vec2(m_Origin.x + PADDING + foodLabel->getContentSize().width / 2, boostersLabel->getPositionY() - PADDING - foodLabel->getContentSize().height / 2),
		m_pFoodValueLabel);
	
	// Menu 
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(HUD::gameOver, this));
	menu_item_pause->setPosition(Vec2(m_Origin.x + VISIBLE_SIZE_WIDTH - menu_item_pause->getContentSize().width / 2,
		m_Origin.y + VISIBLE_SIZE_HEIGHT - menu_item_pause->getContentSize().height / 2));
		
	auto* hudButtonsMenu = Menu::create(menu_item_pause, NULL);
	hudButtonsMenu->setPosition(Point(0, 0));
	this->addChild(hudButtonsMenu);

	//CCLOG("HUD initialized");
	return true;
}

void HUD::initLabelWithValue(Label* label, Vec2 position, Label* value)
{	
	this->addChild(label);
	this->addChild(value);
	label->setPosition(position);
	label->setColor(Color3B(200, 0, 0));
	label->enableOutline(Color4B(0,0,0,255));
	label->enableGlow(Color4B(255, 255, 51, 255));	
	value->setPosition(Vec2(VISIBLE_SIZE_WIDTH * .25, label->getPositionY()));
	value->setColor(Color3B(0, 0, 0));
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

void HUD::gameOver(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->gameLayer()->gameOver();
}