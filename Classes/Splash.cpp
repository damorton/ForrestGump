/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Splash.cpp

	Description: Implements the splash screen

*/

// Includes
#include "Splash.h"
#include "MainMenu.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// createScene - creates the scene using a layer
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

// Init - initialization function
bool Splash::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// Creates and adds backfround for splash screen
	auto splashBackground = Sprite::create("background/Splash.png");
	splashBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(splashBackground);	

	// Creates and adds player sprite to splash screen
	auto player = Sprite::create("sprites/playerRunning01.png");
	player->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(player);

	// Creates and runs a scale action on the player sprite
	auto scale = ScaleBy::create(50, 50);
	player->runAction(scale);

	// Creates and adds particle for splash screen
	CCParticleSystem *ccEmitter = CCParticleSystemQuad::create("particles/BoingStar.plist");
	ccEmitter->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	ccEmitter->setTotalParticles(1000);
	this->addChild(ccEmitter);

	// Runs scheduler to move splash scene to main menu screen
	this->scheduleOnce(schedule_selector(Splash::goToMainMenuScene), DISPLY_TIME_SPLASH_SCENCE);	
	return true;
}


void Splash::goToMainMenuScene(float dt)
{
	// Creates a scene for main menu scene and replaces current scene
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void cleanup()
{
	// Cleanup function
}