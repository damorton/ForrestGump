/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	HUD.h

	Description: HUD layer is responsible by UI (User Interface).
	Score and Distance are some feature controlled by HUD.
	Pause menu is on HUD.

*/

#ifndef HUD_H_
#define	HUD_H_

// Includes
#include "Definitions.h"

// Forward declarations
class Popup;
class Player;

class HUD : public cocos2d::Layer
{
public:		
	// Init
	virtual bool init();

	// Deconstrcutor
	virtual ~HUD(){ this->hudCleanup(); };

	// Initialize the parent node 
	CREATE_FUNC(HUD);

	// Add score
	void addScore();

	// Update
	void update();	

	// Pause game scene
	void pause(CCObject* pSender);

	// Resume game scene
	void resume(CCObject* pSender);

	// Back to Main menu scene
	void mainMenu(CCObject* pSender);

	// Toggle Pause
	void togglePause(bool paused);

	// Initiallize the counter score
	void initLabelWithValue(Label* label, Vec2 position, Label* value);	

	// TODO : Implement clean up function 
	void hudCleanup();
private:

	Size m_Size;
	Vec2 m_Origin;	
	float m_fValuePosX;
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	int m_nBoosters;
	int m_nFood;
	Label* m_pDistanceValueLabel;
	Label* m_pCoinsValueLabel;
	Label* m_pItemsValueLabel;
	Label* m_pBoostersValueLabel;
	Label* m_pFoodValueLabel;
	MenuItemImage *menu_item_pause;
	Popup* popup;
	Player* m_pPlayer;
};

#endif