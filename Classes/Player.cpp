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
	setBPAction(BP_UP);
	m_nDistance = 0;
	m_nCoins = 0;
	m_nBoosters = 0;
	m_nFood = 0;
	m_nItems = 0;
	m_nNumberOfJumps = 0;
	m_bGodMode = true;
	
	this->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height + this->getContentSize().height / 2));
	auto playerPhysicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height - 5), PHYSICSBODY_MATERIAL_DEFAULT);	
	playerPhysicsBody->setDynamic(true);
	playerPhysicsBody->setGravityEnable(true);
	playerPhysicsBody->setRotationEnable(false);
	this->setPhysicsBody(playerPhysicsBody);
	
	// Animate the player
	this->getAnimationWithFrames("sprites/playerRunning%02d.png", 4);


	m_pJetpack = Sprite::create("sprites/jetpackUp.png");
	m_pJetpack->setPosition(Vec2(0, this->getContentSize().height / 2));
	this->addChild(m_pJetpack, -1);
	
	auto jetpackFire = ParticleSystemQuad::create("particles/jetpackFire.plist");		
	jetpackFire->setPosition(Vec2::ZERO);
	jetpackFire->setAutoRemoveOnFinish(true);	
	m_pJetpack->addChild(jetpackFire, 0, "jetpack");

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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_25.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/coin.plist", this->getContentSize().width, this->getContentSize().height, 1, 0.5);
}

void Player::addBooster()
{
	m_nBoosters++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
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

void Player::addParticle()
{
	m_pEmitter = CCParticleSystemQuad::create("particles/Shadow.plist");
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


void Player::jump()
{
	if (m_ePlayerAction == RUNNING)
	{
		m_ePlayerAction = JUMPING;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
		this->getAnimationWithFrames("sprites/playerJumping%02d.png", 3);
		m_nNumberOfJumps++;				
	}
	
	if (m_eBackpackAction == BP_UP)
	{
		m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackDown.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		m_pJetpack->getChildByName("jetpack")->setPosition(Vec2(0, m_pJetpack->getContentSize().height));		
		this->getPhysicsBody()->setVelocity(PLAYER_JUMP_VEL);
		setBPAction(BP_DOWN);
	}
	else if (m_eBackpackAction == BP_DOWN)
	{
		m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackUp.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		m_pJetpack->getChildByName("jetpack")->setPosition(Vec2::ZERO);		
		this->getPhysicsBody()->setVelocity(-PLAYER_JUMP_VEL);
		setBPAction(BP_UP);
	}
}

void Player::update()
{		
	// reset player poisiton 
	this->setPositionX(PLAYER_POSITION_IN_WINDOW);
	if (this->getBoundingBox().intersectsRect(WorldManager::getInstance()->getFloorSprite()->getBoundingBox()))
	{	
		// Running animation		
		if (m_ePlayerAction == JUMPING)
		{			
			this->getAnimationWithFrames("sprites/playerRunning%02d.png", 4);
			m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackUp.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		}
		m_ePlayerAction = RUNNING;			
		setBPAction(BP_UP);
		m_pEmitter->setScale(2.0);
		m_pEmitter->resume();
		m_nNumberOfJumps = 0;
	}
	else
	{				
		m_pEmitter->setScale(0.0);
		m_pEmitter->pause();
	}		

	if (this->getPositionY() > VISIBLE_SIZE_HEIGHT + this->getContentSize().height)
	{
		this->setPositionY(VISIBLE_SIZE_HEIGHT + this->getContentSize().height);
	}		
}

void Player::touch(const Point& location)
{	
	this->jump();	
}

void Player::playerCleanup()
{
	CCLOG("Player cleanup");
}

// Create the Animation Sprites, return animate object
void Player::getAnimationWithFrames(char* enemyAnimation, int frames){
	
	this->stopAllActions();
	Vector<SpriteFrame*> animFrames(4);
	char str[100] = { 0 };
	for (int i = 1; i < frames; i++)
	{
		sprintf(str, enemyAnimation, i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, this->getContentSize().width, this->getContentSize().height)); //we assume that the sprites' dimentions are 40*40 rectangles.
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate = Animate::create(animation);
	auto repeat = RepeatForever::create(animate);	
	this->runAction(repeat);
}
