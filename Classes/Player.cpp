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

void Player::cleanUp()
{
}