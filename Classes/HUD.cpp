#include "HUD.h"
#include "WorldManager.h"

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
	m_iScore = 0;
	
	// Score label	
	m_lScore = LabelTTF::create(std::to_string(m_iScore), "Segoe UI", FONT_SIZE);
	m_lScore->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - m_lScore->getContentSize().height));
	this->addChild(m_lScore, 0);

	// Timer?

	return true;
}

void HUD::updateScore()
{
	m_iScore ++; // update the score
	m_lScore->setString(std::to_string(m_iScore));
}