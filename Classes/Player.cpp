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
	auto action = JumpBy::create(1.5, Point(0,0), 300, 1);
	m_pSprite->runAction(action);
	CCLOG("Player jumped");
}

void Player::cleanUp()
{
}