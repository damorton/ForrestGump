#include "Popup.h"
#include "HUD.h"

USING_NS_CC;

//  Created by Tiago Oliveira on 27/11/14.
//  Copyright Tiago Oliveira 2014. All rights reserved.
//
// Popup Sprite

#include "Popup.h"
#include "GameScene.h"
#include "Definitions.h"
#include "MainMenu.h"
#include "WorldManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

//init create popup element with text
bool Popup::init()
{
	if (!CCSprite::init()) {
		return false;
	}
	// Background Menu	
	auto m = Sprite::create("buttons/menu.png");	

	m->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);	
	this->addChild(m, 1);
	
	// Add menu to my Sprite Pause menu
	this->setVisible(false);
	
	return true;
}

//Popup with title, insert text for parameter
Popup* Popup::createPopup()
{
	Popup *pop = new Popup();
	pop->init();
	pop->autorelease();
	return pop;
}

//Shows up a popup screen
void Popup::show(bool shouldShow)
{
	GameScene *g = WorldManager::gameLayer();

	// Control actions allowed and not allowed
	g->pauseGame();

	// Set my Sprite Pause visible
	this->setVisible(shouldShow);
	
	// Stop sound
	if (shouldShow)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	
}

