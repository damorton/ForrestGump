#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "cocos2d.h"
#include "Popup.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
	virtual ~MainMenu(){ this->mainMenuCleanup(); };
	CREATE_FUNC(MainMenu);

	void playGame(Ref *pSender);
	void leaderboard(Ref *pSender);
	void settings(Ref *pSender);	
	void back(CCObject* pSender);
	void sound(CCObject* pSender);
	void addParticlesToButtons(MenuItemImage* button);
	void mainMenuCleanup();
private:
	MenuItemImage* soundButton;
	bool soundEnabled;
	Popup* popupSettings;
};

#endif 
