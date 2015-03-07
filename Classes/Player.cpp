#include "Definitions.h"
#include "WorldManager.h"
#include "Player.h"
#include "GameOver.h"

Player* Player::create(const std::string& filename)
{
	Player* pSprite = new Player();
	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		pSprite->init();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool Player::init()
{	
	m_strUsername = "David";
	setType(PLAYER);
	setAction(RUNNING);
	setState(ALIVE);
	m_nDistance = 0;
	m_nCoins = 0;
	m_nBoosters = 0;
	m_nFood = 0;
	m_nItems = 0;
	m_nNumberOfJumps = 0;
	
	this->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height + this->getContentSize().height / 2));
	auto playerPhysicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height - 5), PHYSICSBODY_MATERIAL_DEFAULT);	
	playerPhysicsBody->setDynamic(true);
	playerPhysicsBody->setGravityEnable(true);
	playerPhysicsBody->setRotationEnable(false);
	this->setPhysicsBody(playerPhysicsBody);

	//Start player walking
	this->getAnimationWithFrames(1, 4, 1);
	this->runAction(this->animate);

	// add hint sprite


	WorldManager::getInstance()->setPlayer(this);
	CollisionManager::getInstance()->setPlayer(this);
	this->addParticle();

	return true;
}
void Player::addDistance()
{
	m_nDistance++;
}

void Player::addCoin()
{
	m_nCoins++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/coin.plist", this->getContentSize().width, this->getContentSize().height, 1, 0.5);
}

void Player::addBooster()
{
	m_nBoosters++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Boost.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/booster.plist", this->getContentSize().width / 2, 0, 1, 0.5);
}

void Player::addFood()
{
	m_nFood++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Crunch_DavidYoung.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/SplatterParticle2.plist", this->getContentSize().width / 2, this->getContentSize().height / 2, 2, 0.1);
	this->addParticlesGameObjects("particles/Muffin.plist", this->getContentSize().width / 2, 0, 1, 0.5);
}

void Player::addItem()
{
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/DiamondPar3.plist", this->getContentSize().width, this->getContentSize().height, 1, 0.5);
}

void Player::addParticle( )
{
	m_pEmitter = CCParticleSystemQuad::create("particles/shadow.plist");
	m_pEmitter->setPosition(this->getContentSize().width/2, 0);
	m_pEmitter->setEmissionRate(20);
	m_pEmitter->setTotalParticles(100);
	this->addChild(m_pEmitter);
	m_pEmitter->setAutoRemoveOnFinish(true);
	
}

void Player::addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration)
{
	m_pGameObjectEmitter = CCParticleSystemQuad::create(path);
	m_pGameObjectEmitter->setPosition(a, b);
	m_pGameObjectEmitter->setTotalParticles(totalPar);
	m_pGameObjectEmitter->setDuration(duration);
	this->addChild(m_pGameObjectEmitter);
	m_pGameObjectEmitter->setAutoRemoveOnFinish(true);
}

void Player::resetCoins()
{
	m_nCoins = 0;
}

void Player::endGame()
{
	CCLOG("Called");
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOver::createScene()));
}

void Player::jump()
{
	if (m_ePlayerAction == RUNNING || m_nNumberOfJumps < MAX_NO_OF_JUMPS)
	{
		m_nNumberOfJumps++;
		m_ePlayerAction = JUMPING;
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
		this->getPhysicsBody()->applyImpulse(PLAYER_JUMP_VEL);
	}
}

void Player::update()
{		
	// reset player poisiton 
	this->setPositionX(PLAYER_POSITION_IN_WINDOW);
	if (this->getBoundingBox().intersectsRect(WorldManager::getInstance()->getFloorSprite()->getBoundingBox()))
	{		
		m_ePlayerAction = RUNNING;
		m_pEmitter->setScale(2.0);
		m_pEmitter->resume();
		m_nNumberOfJumps = 0;
	}
	else
	{
		m_ePlayerAction = JUMPING;
		m_pEmitter->setScale(0.0);
		m_pEmitter->pause();
	}		
}

void Player::touch(const Point& location)
{
	if (location.x < PLAYER_POSITION_IN_WINDOW) 
	{
		this->jump();
		// if hint sprite touched, set visible false
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
