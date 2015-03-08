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
	distanceLabel->setPosition(Vec2(m_Origin.x + PADDING + distanceLabel->getContentSize().width / 2, m_Origin.y + VISIBLE_SIZE_HEIGHT - PADDING - distanceLabel->getContentSize().height / 2));
	distanceLabel->setColor(Color3B(255, 255, 255));
	distanceLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(distanceLabel);
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(m_nDistance) + "m", LABEL_FONT, LABEL_FONT_SIZE);
	m_pDistanceValueLabel->setPosition(Vec2(distanceLabel->getPositionX() + distanceLabel->getContentSize().width / 2 + PADDING + m_pDistanceValueLabel->getContentSize().width/2, distanceLabel->getPositionY()));
	m_pDistanceValueLabel->setColor(Color3B(255, 255, 64));
	m_pDistanceValueLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(m_pDistanceValueLabel);
	
	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);
	coinsLabel->setPosition(Vec2(m_Origin.x + PADDING + coinsLabel->getContentSize().width / 2, distanceLabel->getPositionY() - distanceLabel->getContentSize().height / 2));
	coinsLabel->setColor(Color3B(255, 255, 255));
	coinsLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(coinsLabel);
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(m_nCoins), LABEL_FONT, LABEL_FONT_SIZE);
	m_pCoinsValueLabel->setPosition(Vec2(coinsLabel->getPositionX() + coinsLabel->getContentSize().width / 2 + PADDING + m_pCoinsValueLabel->getContentSize().width / 2, coinsLabel->getPositionY()));
	m_pCoinsValueLabel->setColor(Color3B(255, 255, 64));
	m_pCoinsValueLabel->enableGlow(Color4B(255, 255, 51, 255));
	this->addChild(m_pCoinsValueLabel);
		
	// Menu 
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(HUD::pauseGame, this));
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
	value->setPosition(Vec2(label->getPositionX() + label->getContentSize().width / 2 + PADDING, label->getPositionY()));
	value->setColor(Color3B(0, 0, 0));
	value->enableGlow(Color4B(255, 255, 51, 255));
}

void HUD::update()
{
	if (WorldManager::getInstance()->getPlayer() != NULL)
	{
		WorldManager::getInstance()->getPlayer()->addDistance();		
		m_pDistanceValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()) + "m");
		m_pCoinsValueLabel->setString(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()));		
	}
}

void HUD::gameOver(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->gameLayer()->gameOver();
}
void HUD::pauseGame(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->gameLayer()->pauseGame();
}
