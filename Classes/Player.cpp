#include "Definitions.h"
#include "WorldManager.h"
#include "Player.h"
#include "GameOver.h"
#include "audio/include/SimpleAudioEngine.h"

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
	setType(PLAYER);
	setAction(RUNNING);
	setState(ALIVE);
	setBPAction(BP_UP);
		
	// Player statistics from local DB
	m_strUsername = WorldManager::getInstance()->getPlayerUsername();
	m_nHighscore = std::atoi(WorldManager::getInstance()->getPlayerHighscore().c_str());
	
	// Player statistics per game
	m_nDistance = 0;
	m_nCoins = 0;
	m_nBoosters = 0;
	m_nFood = 0;
	m_nItems = 0;
	m_nEnemiesKilled = 0;		
	
	// God mode
	m_bGodMode = false;
	m_nCount = 0;
	
	this->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height + this->getContentSize().height / 2));
	auto playerPhysicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height -1), PHYSICSBODY_MATERIAL_DEFAULT);	
	playerPhysicsBody->setDynamic(true);
	playerPhysicsBody->setGravityEnable(true);
	playerPhysicsBody->setRotationEnable(false);
	playerPhysicsBody->setVelocityLimit(MAX_PLAYER_VEL);
	this->setPhysicsBody(playerPhysicsBody);
	
	// Animate the player
	this->getAnimationWithFrames("sprites/playerRunning%02d.png", 4);


	m_pJetpack = Sprite::create("sprites/jetpackUp.png");
	m_pJetpack->setPosition(Vec2(0, this->getContentSize().height / 2));
	this->addChild(m_pJetpack, -1);
	
	auto jetpackFire = ParticleSystemQuad::create("particles/jetpackFire.plist");		
	jetpackFire->setPosition(Vec2::ZERO);
	jetpackFire->setAutoRemoveOnFinish(true);	
	jetpackFire->setScale(0.4);
	m_pJetpack->addChild(jetpackFire, 0, "jetpackFire");

	m_pShield = Sprite::create("sprites/shield.png");
	m_pShield->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	m_pShield->setVisible(false);
	this->addChild(m_pShield);

	WorldManager::getInstance()->setPlayer(this);
	CollisionManager::getInstance()->setPlayer(this);
	this->addParticle();

	return true;
}

void Player::addDistance()
{
	
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
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/booster.plist", this->getContentSize().width / 2, 0, 1, 0.5);

}

void Player::addFood()
{
	m_nFood++;
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/SplatterParticle2.plist", this->getContentSize().width / 2, this->getContentSize().height / 2, 2, 0.1);
	this->addParticlesGameObjects("particles/Muffin.plist", this->getContentSize().width / 2, 0, 1, 0.5);
}

void Player::addItem()
{
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
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

void Player::setGodMode()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Powerup_32.wav", false, 1.0, 1.0, 1.0);
	m_bGodMode = true;
	m_nCount = 0;	
	m_pShield->setVisible(true);	
}

void Player::unsetGodMode()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Powerup_32.wav", false, 1.0, 1.0, 1.0);
	m_bGodMode = false;
	m_pShield->setVisible(false);
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
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);		
	}	
	
	if (m_eBackpackAction == BP_UP)
	{
		m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackDown.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		m_pJetpack->getChildByName("jetpackFire")->setPosition(Vec2(0, m_pJetpack->getContentSize().height));				
		setBPAction(BP_DOWN);
		this->getPhysicsBody()->setVelocity(PLAYER_JUMP_VEL);
	}
	else if (m_eBackpackAction == BP_DOWN)
	{
		m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackUp.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		m_pJetpack->getChildByName("jetpackFire")->setPosition(Vec2::ZERO);			
		setBPAction(BP_UP);
		this->getPhysicsBody()->setVelocity(-PLAYER_JUMP_VEL);
	
	}
}

void Player::update()
{			
	m_nDistance++;

	if (isGod())
	{
		m_nCount++;
		if (m_nCount > 500)
		{
			this->unsetGodMode();
			m_nCount == 0;
		}		
	}	

	// reset player poisiton 
	this->setPositionX(PLAYER_POSITION_IN_WINDOW);
	if (this->getBoundingBox().intersectsRect(WorldManager::getInstance()->getFloorSprite()->getBoundingBox()))
	{	
		// Running animation		
		if (m_ePlayerAction == JUMPING)
		{			
			this->getAnimationWithFrames("sprites/playerRunning%02d.png", 4);
			m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackUp.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
			m_pJetpack->getChildByName("jetpackFire")->setPosition(Vec2::ZERO);
			m_ePlayerAction = RUNNING;
			setBPAction(BP_UP);
			m_pEmitter->setScale(1.0);
			m_pEmitter->resume();
		}		
	}
	else
	{
		if (m_ePlayerAction == RUNNING)
		{			
			this->getAnimationWithFrames("sprites/playerJumping%02d.png", 3);
			m_ePlayerAction = JUMPING;
			m_pEmitter->setScale(0.0);
			m_pEmitter->pause();
		}		
	}

	// reset player poisiton 
	this->setPositionX(PLAYER_POSITION_IN_WINDOW);
			

	if (this->getPositionY() > VISIBLE_SIZE_HEIGHT - this->getContentSize().height)
	{
		this->setPositionY(VISIBLE_SIZE_HEIGHT - this->getContentSize().height);
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
