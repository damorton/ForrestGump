#include "Player.h"

Player::Player(std::string name)
{
	m_strName = name;
	init();
}

bool Player::init()
{	
	setType(EGameOjectType::PLAYER);
	m_fPlayerXPos = m_pSprite->getPositionX();
	return true;
}

void Player::update()
{
	CCLOG("PLayer update");	
	m_pSprite->setPositionX(m_fPlayerXPos);
}

void Player::jump()
{	
	CCLOG("Player jumped Angular velocity %f", m_pSprite->getPhysicsBody()->getAngularVelocity());
	auto action = JumpBy::create(2, Vec2(50, 150), 80, 1);
	m_pSprite->runAction(action);
}

void Player::moveLeft()
{
	CCLOG("Player moved left by velocity %f", m_pSprite->getPhysicsBody()->getAngularVelocity());
	auto action = MoveBy::create(2, Vec2(-100, 0));
	m_pSprite->runAction(action);
}

void Player::moveRight()
{
	CCLOG("Player jumped right by velocity %f", m_pSprite->getPhysicsBody()->getAngularVelocity());
	auto action = MoveBy::create(2, Vec2(100, 0));
	m_pSprite->runAction(action);
}

void Player::touch(const Point& location)
{
	auto winSize = Director::getInstance()->getWinSize();
	
	// walk
	if (location.y < (winSize.height * 0.5f) && location.x < (winSize.width * 0.5f))
	{
		moveLeft();
	}

	else if (location.y < (winSize.height * 0.5f) && location.x > (winSize.width * 0.5f))
	{
		moveRight();
	}

	// jump
	else
	{
	
		jump();
	}
}

void Player::cleanUp()
{
}
