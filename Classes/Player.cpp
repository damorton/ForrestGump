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
		pSprite->addParticle(pSprite);
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

void Player::addParticle(Player* pS){

ccEmitter = CCParticleSystemQuad::create("Flower.plist");
ccEmitter->setPosition(Point(pS->getPosition().x, pS->getPosition().y));
ccEmitter->setEmissionRate(20.00);
ccEmitter->setTotalParticles(20);
pS->addChild(ccEmitter);
}

void Player::jump()
{
	if (m_ePlayerState == RUNNING)
	{
		m_ePlayerState = JUMPING;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump3.wav", false, 1.0f, 1.0f, 1.0f);
		auto action = JumpBy::create(JUMP_SPEED, Vec2(0, 0), JUMP_HEIGHT, NO_OF_JUMPS);
		this->runAction(action);
		this->runAction(AnimationMoves::getAnimationWithFrames(1, 2));
		CCLOG("Player jumped");
	}
}

void Player::update()
{	
	if (this->getBoundingBox().intersectsRect(WorldManager::getInstance()->getFloorSprite()->getBoundingBox()))
	{		
		m_ePlayerState = RUNNING;
		ccEmitter->setScale(1.0);
		ccEmitter->resume();
		
	}
	else
	{
		m_ePlayerState = JUMPING;	
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("trashdropping.wav", false, 1.0f, 1.0f, 1.0f);

		ccEmitter->setScale(0.0);
		ccEmitter->pause();
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
