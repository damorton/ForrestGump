#include "Enemy.h"
#include "WorldManager.h"
#include "Definitions.h"

USING_NS_CC;

Enemy* Enemy::create(const std::string& filename)
{
	Enemy* pSprite = new Enemy();

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

bool Enemy::init()
{
	setType(ENEMY);	
	return true;
}

/*
	Run the enemy AI
*/
void Enemy::runAI()
{
	CCLOG("Running Enemy AI");
}

/*
	Update the enemy
*/
void Enemy::update()
{
	CCLOG("Updating Enemy");
}

/*
	Enemy cleanup
*/
void Enemy::cleanUp()
{	CCLOG("Enemy::cleanUp()");

}

/*
Function to spawn enemies
*/
void Enemy::spawnEnemy(Layer *layer){

	// using singleton to get info for our obstacle spawns
	auto visbleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// creating obstacles
	auto m_groundEnemy = Enemy::create("sprites/Enemy2.png");
	auto m_floatingEnemy = Enemy::create("sprites/Enemy.png");

	// creating physics body around obstacles
	auto m_groundEnemyBody = PhysicsBody::createBox(m_groundEnemy->getContentSize());
	auto m_floatingEnemyBody = PhysicsBody::createBox(m_floatingEnemy->getContentSize());

	auto m_groundEnemyY = (CCRANDOM_0_1() * visbleSize.height) + 150;
	auto m_floatingEnemyY = (CCRANDOM_0_1() * visbleSize.height);

	// dynamic bodies are not affected by gravity
	// we should totally experiment with this!
	m_groundEnemyBody->setDynamic(false);
	m_groundEnemyBody->setGravityEnable(false);
	m_groundEnemyBody->setDynamic(true);

	m_floatingEnemyBody->setGravityEnable(false);
	m_floatingEnemyBody->setDynamic(true);



	// setting physics bodies for enemies
	m_groundEnemy->setPhysicsBody(m_groundEnemyBody);
	m_floatingEnemy->setPhysicsBody(m_floatingEnemyBody);

	// setting positions of enemies
	m_groundEnemy->setPosition(Point(visbleSize.width + origin.x, WorldManager::getInstance()->getFloorSprite()->getPositionY() + m_groundEnemy->getContentSize().height * 2)); // setting postion to be above floor
	m_floatingEnemy->setPosition(Point(visbleSize.width + origin.x, m_floatingEnemyY));

	// adding obstacles to the scene
	layer->addChild(m_groundEnemy, 1);
	layer->addChild(m_floatingEnemy, 1);

	// setting velocity of enemies to give illusion of runner
	auto m_groundEnemyAction = MoveBy::create(ENEMY_MOVEMENT_SPEED * visbleSize.width, Point(-visbleSize.width *1.5, 0));
	auto m_floatingEnemyAction = MoveTo::create(ENEMY_MOVEMENT_SPEED * visbleSize.width, Point(WorldManager::getInstance()->getPlayer()->getPositionX(), WorldManager::getInstance()->getPlayer()->getPositionY()));

	m_groundEnemy->runAction(m_groundEnemyAction);
	m_floatingEnemy->runAction(m_floatingEnemyAction);

}

//This is the animation Function, look Player.cpp to know how to use me
void Enemy::getAnimationWithFrames(int init, int end){
	Vector<SpriteFrame*> animFrames(2);
	char str[100] = { 0 };
	int i = init;
	while (i <= end)
	{
		sprintf(str, "sprites/walk%02d.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 105, 135)); //we assume that the sprites' dimentions are 105*135 rectangles.
		i++;
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
}