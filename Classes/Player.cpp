/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Player.cpp

	Description: The player class handles all player functionality. It
	keeps track on the player current state and actions at all times. We handle
	touches here also by registering the touch to make the player jump etc.

*/

// Includes
#include "Player.h"
#include "WorldManager.h"
#include "CollisionManager.h"
#include "audio/include/SimpleAudioEngine.h"

// Creates the Player
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

// Initialize the player class
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
	
	// Set the player position
	this->setPosition(Vec2(PLAYER_POSITION_IN_WINDOW, SCREEN_ORIGIN.y + WorldManager::getInstance()->getFloorSprite()->getContentSize().height + this->getContentSize().height / 2));
	
	// Set physics for the player
	auto playerPhysicsBody = PhysicsBody::createBox(Size(this->getContentSize().width, this->getContentSize().height -1), PHYSICSBODY_MATERIAL_DEFAULT);	
	playerPhysicsBody->setDynamic(true);
	playerPhysicsBody->setGravityEnable(true);
	playerPhysicsBody->setRotationEnable(false);
	playerPhysicsBody->setVelocityLimit(MAX_PLAYER_VEL);
	this->setPhysicsBody(playerPhysicsBody);
	
	// Animate the player
	this->getAnimationWithFrames("sprites/playerRunning%02d.png", 4);

	// Create jetpack for the player
	m_pJetpack = Sprite::create("sprites/jetpackUp.png");
	m_pJetpack->setPosition(Vec2(0, this->getContentSize().height / 2));
	this->addChild(m_pJetpack, -1);
	
	// Create particles for the players jetpack
	auto jetpackFire = ParticleSystemQuad::create("particles/jetpackFire.plist");		
	jetpackFire->setPosition(Vec2::ZERO);
	jetpackFire->setAutoRemoveOnFinish(true);	
	jetpackFire->setScale(0.4);
	m_pJetpack->addChild(jetpackFire, 0, "jetpackFire");

	// Create the force field shield for the player
	m_pShield = Sprite::create("sprites/shield.png");
	m_pShield->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	m_pShield->setVisible(false);
	this->addChild(m_pShield);

	WorldManager::getInstance()->setPlayer(this);
	CollisionManager::getInstance()->setPlayer(this);
	this->addParticle();

	return true;
}

// Adds coins to the count when player collects coins
void Player::addCoin()
{
	m_nCoins++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Pickup_Coin28.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/Coins2.plist", this->getContentSize().width, this->getContentSize().height, 2, 1, 0.09);
}

// Adds boosters to the count when player collects boosters
void Player::addBooster()
{
	m_nBoosters++;
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/booster.plist", this->getContentSize().width / 2, 0, 2, 0.5, 0.3);

}

// Adds food to the count when player collects food
void Player::addFood()
{
	m_nFood++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/Crunch_DavidYoungShorter.wav", false, 1.0f, 1.0f, 1.0f);
	m_nItems++;
   this->addParticlesGameObjects("particles/SplatterParticle2.plist", this->getContentSize().width / 2, this->getContentSize().height / 2, 2, 0.1, 0.5);
   this->addParticlesGameObjects("particles/Muffin.plist", this->getContentSize().width / 2, this->getContentSize().height, 2, 0.5, 0.3);
}

// Adds items to the count when player collects items
void Player::addItem()
{
	m_nItems++;
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);
	this->addParticlesGameObjects("particles/DiamondPar3.plist", this->getContentSize().width, this->getContentSize().height, 2, 0.5, 0.3);
}

// Adds Particles effects
void Player::addParticle()
{
	m_pEmitter = CCParticleSystemQuad::create("particles/Shadow.plist");
	m_pEmitter->setPosition(this->getContentSize().width/2, 0);
	m_pEmitter->setEmissionRate(20);
	m_pEmitter->setTotalParticles(100);
	this->addChild(m_pEmitter);
	m_pEmitter->setAutoRemoveOnFinish(true);
	
}

// Activate the shield
void Player::setGodMode()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Powerup_32.wav", false, 1.0, 1.0, 1.0);
	m_bGodMode = true;
	m_nCount = 0;	
	m_pShield->setVisible(true);	
}

// Deactivate the shield
void Player::unsetGodMode()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Powerup_32.wav", false, 1.0, 1.0, 1.0);
	m_bGodMode = false;
	m_pShield->setVisible(false);
}

// Adds Particle Effects to the objects
void Player::addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration, float scale)
{
    m_pGameObjectEmitter = ParticleSystemQuad::create(path);
	m_pGameObjectEmitter->setPosition(a, b);
	m_pGameObjectEmitter->setTotalParticles(totalPar);
	m_pGameObjectEmitter->setDuration(duration);
	m_pGameObjectEmitter->setAutoRemoveOnFinish(true);
	m_pGameObjectEmitter->setScale(scale);
	this->addChild(m_pGameObjectEmitter);
	
}

// Player jump method
void Player::jump()
{	
	// If player is running when jump is called
	if (m_ePlayerAction == RUNNING)
	{
		// Play a jump sound effect
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/SFX_Pickup_40.wav", false, 1.0f, 1.0f, 1.0f);		
	}	
	// If back pack action = BP_UP and jump is pressed
	if (m_eBackpackAction == BP_UP)
	{
		// send player down
		m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackDown.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		m_pJetpack->getChildByName("jetpackFire")->setPosition(Vec2(0, m_pJetpack->getContentSize().height));				
		setBPAction(BP_DOWN);
		this->getPhysicsBody()->setVelocity(PLAYER_JUMP_VEL);
	}
	// else if action == BP_DOWN
	else if (m_eBackpackAction == BP_DOWN)
	{
		// jump player up
		m_pJetpack->setSpriteFrame(SpriteFrame::create("sprites/jetpackUp.png", Rect(0, 0, m_pJetpack->getContentSize().width, m_pJetpack->getContentSize().height)));
		m_pJetpack->getChildByName("jetpackFire")->setPosition(Vec2::ZERO);			
		setBPAction(BP_UP);
		this->getPhysicsBody()->setVelocity(-PLAYER_JUMP_VEL);
	
	}
}

// Player update method
void Player::update()
{			
 
	//CCLOG("-------------UPDATING PLAYER--------------");
	m_nDistance++;

	// Increment player distance travelled
	m_nDistance++;

	// If player is in god mode
	if (isGod())
	{
		// Increase count
		m_nCount++;

		// If count is greater than 500
		if (m_nCount > 500)
		{
			// Turn off god mode
			this->unsetGodMode();

			// Reset count
			m_nCount = 0;
		}		
	}	

	// Reset player poisiton in window
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

	// Jumping animation
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

	// Reset player poisiton 
	this->setPositionX(PLAYER_POSITION_IN_WINDOW);
			

	if (this->getPositionY() > VISIBLE_SIZE_HEIGHT)
	{
		this->setPositionY(VISIBLE_SIZE_HEIGHT);
	}		
}

// On touch screen, hero jumps
void Player::touch(const Point& location)
{	
	this->jump();	
}

// TODO : Implement clean up function 
void Player::playerCleanup()
{
	//CCLOG("Player cleanup");
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



// Effects for Enemy death
void Player::addEnemyDeathParticle()
{
	auto EnemyDeathParticle = ParticleSystemQuad::create("particles/EnemyDeath.plist");
	EnemyDeathParticle->setPosition(this->getContentSize().width, this->getContentSize().height);
	EnemyDeathParticle->setAutoRemoveOnFinish(true);
	EnemyDeathParticle->setScale(0.2);
	this->addChild(EnemyDeathParticle);
}

// Pause hero movement
void Player::pausePlayer()
{
	// Pause the player
	m_pJetpack->getChildByName("jetpackFire")->pause();
	this->pause();	
}

// Resume hero movement
void Player::resumePlayer()
{
	m_pJetpack->getChildByName("jetpackFire")->resume();
	this->resume();	
}

