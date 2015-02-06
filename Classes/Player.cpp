#include "WorldManager.h"
#include "Player.h"

Player* Player::create(const std::string& filename)
{
	Player* pSprite = new Player();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		pSprite->init();
		//pSprite->addEvents();
		return pSprite;
	}

	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool Player::init()
{	
	setType(PLAYER);
	setState(RUNNING);		
	return true;
}

void Player::jump()
{
	if (m_ePlayerState == RUNNING)
	{
		m_ePlayerState = JUMPING;
		auto action = JumpBy::create(1.5, Vec2(0, 0), 300, 1);
		this->runAction(action);
		CCLOG("Player jumped");
	}
}

void Player::update()
{
	/*
		Issue - Player sprite sinking into the floor sprite

		Solution - Reset the players position if the players bounding box collides with the floor 
		bounding box
	*/	
	if (this->getBoundingBox().intersectsRect(WorldManager::getInstance()->getFLoorSprite()->getBoundingBox()))
	{		
		this->setPositionY(WorldManager::getInstance()->getFLoorSprite()->getPositionY() +
			(WorldManager::getInstance()->getFLoorSprite()->getContentSize().height / 3) * 2 +
			this->getContentSize().height / 2);
		m_ePlayerState = RUNNING;
	}
}

void Player::cleanUp()
{
}
