#ifndef HUD_H_
#define	HUD_H_

#include "cocos2d.h"
#include "Popup.h"
#include "Player.h"

USING_NS_CC;

class HUD : public cocos2d::Layer
{
public:		
	virtual bool init();
	virtual ~HUD(){ this->hudCleanup(); };
	CREATE_FUNC(HUD);

	void addScore();
	void update();	
	void pause(CCObject* pSender);
	void resume(CCObject* pSender);
	void mainMenu(CCObject* pSender);
	void togglePause(bool paused);
	void initLabelWithValue(Label* label, Vec2 position, Label* value);	
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
	Popup* popup;
	MenuItemImage *menu_item_pause;
	Player* m_pPlayer;
};

#endif