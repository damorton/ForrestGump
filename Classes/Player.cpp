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
		pSprite->addParticle(pSprite);		
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool Player::init()
{	
	setType(PLAYER);
	setState(RUNNING);
	m_nDistance = 0;
	m_nCoins = 0;
	m_nBoosters = 0;
	m_nFood = 0;
	m_nItems = 0;
	return true;
}

void Player::addParticle(Player* pS){

ccEmitter = CCParticleSystemQuad::create("particles/Flower.plist");
ccEmitter->setPosition(Point(pS->getPosition().x, pS->getPosition().y));
ccEmitter->setEmissionRate(20.00);
ccEmitter->setTotalParticles(20);
pS->addChild(ccEmitter);
}

void Player::jump()
{
	if (m_ePlayerState == RUNNING)
	{
		this->stopAllActions();

		m_ePlayerState = JUMPING;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump3.wav", false, 1.0f, 1.0f, 1.0f);
		auto action = JumpBy::create(JUMP_SPEED, Vec2(0, 0), JUMP_HEIGHT, NO_OF_JUMPS);
		this->runAction(action);
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
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/trashdropping.wav", false, 1.0f, 1.0f, 1.0f);
		ccEmitter->setScale(0.0);
		ccEmitter->pause();
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
