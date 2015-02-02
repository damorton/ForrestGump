#include "Player.h"

Player::Player(std::string name)
{
	m_strName = name;
	init();
}

bool Player::init()
{	
	setType(EGameOjectType::PLAYER);	
	return true;
}

void Player::update()
{
	CCLOG("PLayer update");	
	
}

void Player::jump()
{	
	CCLOG("Player jumped Angular velocity %f", m_pSprite->getPhysicsBody()->getAngularVelocity());
	auto action = JumpTo::create(2, Vec2(100, 100), 50, 1);
	m_pSprite->runAction(action);
}

void Player::cleanUp()
{
}