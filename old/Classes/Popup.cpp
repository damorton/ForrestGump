#include "Popup.h"
#include "HUD.h"
#include "Popup.h"
#include "GameScene.h"
#include "Definitions.h"
#include "MainMenu.h"
#include "WorldManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

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
void Popup::show(bool shouldShow, bool sel)
{
	if (sel)
	{
		GameScene *g = WorldManager::gameLayer();

		// Control actions allowed and not allowed
		g->pauseGame();

		// Stop sound
		if (shouldShow)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
	// Set my Sprite Pause visible
	this->setVisible(shouldShow);
	
}
