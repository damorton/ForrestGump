#include "Popup.h"
#include "HUD.h"

USING_NS_CC;

//  Created by Tiago Oliveira on 27/11/14.
//  Copyright Tiago Oliveira 2014. All rights reserved.
//
// Popup Sprite

#include <iostream>
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

	//Be sure that no menu have created so far
	cont = 0;

	// Background Menu
	CCSprite *m = CCSprite::createWithSpriteFrameName("buttons/menu.png");
	m->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);	
	this->addChild(m, 1);

	// Buttons
	// create the Pause menu items
	auto resumeButton = MenuItemImage::create("buttons/btNotResumeGame.png", "buttons/btActResumeGame.png", CC_CALLBACK_1(Popup::resume, this));
	auto mainMenuButton = MenuItemImage::create("buttons/btNotMainGame.png", "buttons/btActMainGame.png", CC_CALLBACK_1(Popup::mainMenu, this));

	// position the menu buttons on screen
	resumeButton->setPosition(VISIBLE_SIZE_WIDTH / 2, (VISIBLE_SIZE_HEIGHT / 3) + 150);
	mainMenuButton->setPosition(VISIBLE_SIZE_WIDTH / 2, VISIBLE_SIZE_HEIGHT / 2);

	// create menu and add menu items
	auto* menu = Menu::create(resumeButton, mainMenuButton, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	// Add menu to my Sprite Pause menu
	this->setVisible(false);

	return true;
}

void Popup::pauseGame()
{
	WorldManager::getInstance()->hudLayer()->pause;
}

void Popup::mainMenu()
{
	WorldManager::getInstance()->hudLayer()->mainMenu;
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
	if (shouldShow) {
		g->pauseSchedulerAndActions();
	}
	else {
		g->resumeSchedulerAndActions();
	}

	// Stop all the nodes in action in execution (animation, parallax, HUD, etc)
	for (int i = 0; i < g->getChildrenCount(); i++) {
		CCNode *n = (CCNode *)g->getChildren().at(i);
		if (shouldShow) {
			n->pauseSchedulerAndActions();
		}
		else {
			n->resumeSchedulerAndActions();
		}
	}

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

