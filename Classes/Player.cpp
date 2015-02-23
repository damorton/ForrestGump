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

	//getAnimationWithFrames(1, 4, 1);	
	//this->runAction(RepeatForever::create(animate));

	return true;
}

void Player::addCoin()
{
	m_nCoins++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin.wav", false, 1.0f, 1.0f, 1.0f);

}

void Player::addBooster()
{
	m_nBoosters++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin.wav", false, 1.0f, 1.0f, 1.0f);
}

void Player::addFood()
{
	m_nFood++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin.wav", false, 1.0f, 1.0f, 1.0f);
}

void Player::addItem()
{
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin.wav", false, 1.0f, 1.0f, 1.0f);
}
void Player::addParticle(Player* pS)
{
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
		m_ePlayerState = JUMPING;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump3.wav", false, 1.0f, 1.0f, 1.0f);
		
		//Stop the Running animation Forever
		this->stopAllActions();

		//Create the Jump Animation
		getAnimationWithFrames(1, 3, 2);		
		Animate* animate2 = animate; //jumping

		//Create the Running Animation
		getAnimationWithFrames(1, 4, 1);
		Animate* animate3 = animate; //running	

		//Create the Sequence of Animation
		FiniteTimeAction* animationSequence = Sequence::create(animate2, animate3, nullptr);
		this->runAction(animationSequence);

		//NEW JUMP
		CCLOG("jump");
		Vec2 impulse(0.0f, 0.0f);	
		impulse.y = 50000.0f;
		impulse.x = 0.0f;
		this->getPhysicsBody()->applyImpulse(impulse);
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
<<<<<<< HEAD
<<<<<<< HEAD
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/trashdropping.wav", false, 1.0f, 1.0f, 1.0f);
=======
>>>>>>> 17652b915d5a86e78460c575d39c9fd4934162a7
=======

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/trashdropping.wav", false, 1.0f, 1.0f, 1.0f);


>>>>>>> georgina_audio
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

/*
Animation Function
Return Animate object, parameters: 
	init:	initial image, 
	end:	end image, which animation image
	act:	action, which animation
*/
void Player::getAnimationWithFrames(int init, int end, int act){
	Vector<SpriteFrame*> animFrames(4);
	char str[100] = { 0 };
	int i = init;
	while (i <= end)
	{
		if (act == 1)		//1 - Running
		{
			//sprintf(str, "sprites/walk%02d.png", i);
			//auto frame = SpriteFrame::create(str, Rect(0, 0, 105, 135)); //we assume that the sprites' dimentions are 105*135 rectangles.
			sprintf(str, "sprites/walk%02dsmall.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 55, 69)); //we assume that the sprites' dimentions are 55*69 rectangles.
			i++;
			animFrames.pushBack(frame);
		}
		else if (act == 2)	//2 - Jumping
		{
			sprintf(str, "sprites/jump%02dsmall.png", i);
			auto frame = SpriteFrame::create(str, Rect(0, 0, 55, 69)); //we assume that the sprites' dimentions are 55*69 rectangles.
			i++;
			animFrames.pushBack(frame);
		}
	}

	//Define number of loops
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
		if(act == 2) animation->setLoops(4);
		else if (act == 1) animation->setLoops(-1);
	animate = Animate::create(animation);
}
