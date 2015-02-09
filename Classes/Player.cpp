#include "Definitions.h"
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
		auto action = JumpBy::create(JUMP_SPEED, Vec2(0, 0), JUMP_HEIGHT, NO_OF_JUMPS);
		this->runAction(action);
		CCLOG("Player jumped");
	}
}

void Player::update()
{	
	if (this->getBoundingBox().intersectsRect(WorldManager::getInstance()->getFloorSprite()->getBoundingBox()))
	{		
		m_ePlayerState = RUNNING;
	}
	else
	{
		m_ePlayerState = JUMPING;
	}
}

/* Player touch function */
void Player::touch(const Point& location)
{
	// get window size to check where touches
	auto winSize = Director::getInstance()->getWinSize();

	// jump
	if (location.x < PLAYER_POSITION_IN_WINDOW) // jump if user touches behind player position
	{
		jump();
	}

}

void Player::cleanUp()
{
}
