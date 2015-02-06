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
	setState(JUMPING);
	auto action = JumpBy::create(2, Vec2(0, 0), 150, 1);
	this->runAction(action);
	CCLOG("Player jumped");		
}

/* Player touch function */
void Player::touch(const Point& location)
{
	// get window size to check where touches
	auto winSize = Director::getInstance()->getWinSize();

	// jump
	if (location.x < (winSize.width * 0.33f)) // jump if user touches behind player position
	{
		jump();
	}

}

void Player::cleanUp()
{
}
