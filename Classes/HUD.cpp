#include "HUD.h"
#include "WorldManager.h"
#include "Definitions.h"
#include "GameScene.h"

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
	auto scoreTag = Label::createWithTTF("Score ", "fonts/Marker Felt.ttf", FONT_SIZE);
	scoreTag->enableShadow();
	scoreTag->enableGlow(Color4B::RED);
	scoreTag->setPosition(Vec2(PADDING + origin.x + scoreTag->getContentSize().width / 2, origin.y + visibleSize.height - PADDING - scoreTag->getContentSize().height / 2));
	this->addChild(scoreTag);
	
	m_iScore = 0;

	// Score label		
	m_lScore = Label::createWithTTF(std::to_string(m_iScore), "fonts/Marker Felt.ttf", FONT_SIZE, Size(scoreTag->getContentSize().width, FONT_SIZE), TextHAlignment::LEFT, TextVAlignment::TOP);
	m_lScore->enableShadow();	
	m_lScore->enableGlow(Color4B::RED);
	m_lScore->setPosition(Vec2(PADDING + scoreTag->getContentSize().width + m_lScore->getContentSize().width / 2, scoreTag->getPositionY()));
	this->addChild(m_lScore, 0);

	// pause button
	auto menu_item_pause = MenuItemImage::create("buttons/PauseNormal.png", "buttons/PauseSelected.png", CC_CALLBACK_1(GameScene::Pause, this));
	menu_item_pause->setPosition(Vec2(origin.x + visibleSize.width - menu_item_pause->getContentSize().width / 2,
		origin.y + visibleSize.height - menu_item_pause->getContentSize().height / 2));

	// create menu, add menu items and add to the game scene
	auto* menu = Menu::create(menu_item_pause, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	// Timer?
		
	return true;
}

void HUD::updateScore()
{
	m_iScore++;
	m_lScore->setString(std::to_string(m_iScore));	
}