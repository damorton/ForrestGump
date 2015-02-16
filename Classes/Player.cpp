#include "Definitions.h"
#include "WorldManager.h"
#include "AnimationMoves.h"
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
		this->stopAllActions();

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

		

	//	m_pAnimation->getAnimationWithFrames();
	//	this->runAction(RepeatForever::create(m_pAnimation->animate));
		getAnimationWithFrames();
		this->runAction(RepeatForever::create(animate));

	}		
}

void Player::touch(const Point& location)
{
	if (location.x < PLAYER_POSITION_IN_WINDOW) 
	{
		this->jump();
	}
}

void Player::cleanUp()
{
}

void Player::getAnimationWithFrames(){
	//ANIMATION
	Vector<SpriteFrame*> animFrames(4);
	char str[100] = { 0 };
	int i = 1;
	while (i <= 2)
	{
		sprintf(str, "sprites/walk%02d.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 100, 128)); //we assume that the sprites' dimentions are 40*40 rectangles.
		i++;
		animFrames.pushBack(frame);
		sprintf(str, "sprites/walk%02d.png", i);
		auto frame1 = SpriteFrame::create(str, Rect(0, 0, 100, 128)); //we assume that the sprites' dimentions are 40*40 rectangles.
		i++;
		animFrames.pushBack(frame1);
		i++;
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
	
	//END ANIMATION
}
