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
	auto scoreTag = Label::createWithTTF("Score ", "fonts/Marker Felt.ttf", FONT_SIZE);
	scoreTag->setPosition(Vec2(PADDING + origin.x + scoreTag->getContentSize().width / 2, origin.y + visibleSize.height - PADDING - scoreTag->getContentSize().height / 2));
	this->addChild(scoreTag);
	
	m_iScore = 0;

	// Score label		
	m_lScore = Label::createWithTTF(std::to_string(m_iScore), "fonts/Marker Felt.ttf", FONT_SIZE, Size(scoreTag->getContentSize().width, FONT_SIZE), TextHAlignment::LEFT, TextVAlignment::TOP);
	m_lScore->enableShadow();	
	m_lScore->enableGlow(Color4B::RED);
	m_lScore->setPosition(Vec2(scoreTag->getContentSize().width + m_lScore->getContentSize().width / 2, scoreTag->getPositionY()));
	this->addChild(m_lScore, 0);

	// Timer?
		
	return true;
}

void HUD::updateScore()
{
	m_iScore++;
	m_lScore->setString(std::to_string(m_iScore));
}