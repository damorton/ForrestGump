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
	if (!getState() == JUMPING)
	{
		setState(JUMPING);
		auto action = JumpBy::create(2, Vec2(0, 0), 150, 1);
		this->runAction(action);
		CCLOG("Player jumped");
	}	
}

void Player::cleanUp()
{
}
