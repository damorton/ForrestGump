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
	return true;
}

void Player::jump()
{
	CCLOG("Player jumped");
	auto action = JumpBy::create(2, Vec2(0, 0), 150, 1);
	this->runAction(action);
}

void Player::cleanUp()
{
}
