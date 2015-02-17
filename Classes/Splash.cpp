#include "Splash.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "WorldManager.h"

USING_NS_CC;

Scene* Splash::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Splash::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Splash::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto splashBackground = Sprite::create("background/Splash.png");
	splashBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(splashBackground);	

	// particle testing for splash screen
	CCParticleSystem *ccEmitter = CCParticleSystemQuad::create("particles/Flower.plist");
	ccEmitter->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 8) * 2));
	ccEmitter->setTotalParticles(1000);
	ccEmitter->setGravity(ccp(-100.00, 100.00));
	this->addChild(ccEmitter);

	this->scheduleOnce(schedule_selector(Splash::goToMainMenuScene), DISPLY_TIME_SPLASH_SCENCE);	
	return true;
}

void Splash::goToMainMenuScene(float dt)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void cleanup()
{

}