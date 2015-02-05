#include "Player.h"

bool Player::init()
{	

	if (!Sprite::init())
	{
		return false;
	}

	//this->scheduleUpdate();
	return true;
}

void Player::update(float delta)
{
	CCLOG("PLayer update");		
}

void Player::cleanUp()
{
}
