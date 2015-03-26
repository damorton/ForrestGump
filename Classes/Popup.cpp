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
		//GameScene *g = WorldManager::gameLayer();
		//g->pauseGame();
		//auto gameLayer = Director::getInstance()->getRunningScene()->getChildByTag(TAG_GAME_LAYER);		

		// Stop sound
		if (shouldShow)
		{			
			//CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			//gameLayer->pause();
			//WorldManager::getInstance()->layerWithTag(TAG_GAME_LAYER)->pause();			
		}
		else
		{
			//CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			//gameLayer->resume();
			//WorldManager::getInstance()->layerWithTag(TAG_GAME_LAYER)->resume();						
		}
	}
	// Set my Sprite Pause visible
	this->setVisible(shouldShow);	
}
