#include "SplashScene.h"
#include "MainMenuScene.h"
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

	this->scheduleOnce(schedule_selector(Splash::goToMainMenuScene), DISPLY_TIME_SPLASH_SCENCE);

	auto splashBackground = Sprite::create("SplashScene/Splash.png");
	splashBackground->setScale(WorldManager::getInstance()->getGameScale());
	this->addChild(splashBackground);

	auto backgroundSprite = Sprite::create("SplashScene/ForrestGump.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	return true;
}

void Splash::goToMainMenuScene(float dt)
{
	auto scene = MainMenu::createScene();

	Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene));
}