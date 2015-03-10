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
	static void mainMenu();
	MenuItemImage *soundButton;
	bool soundEnabled;

	void playGame(Ref *pSender);
	void leaderboard(Ref *pSender);
	void settings(Ref *pSender);	
	void back(CCObject* pSender);
	void sound(CCObject* pSender);
	
	Popup* popupSettings;
	CREATE_FUNC(MainMenu);

};

#endif // __MAINMENU_SCENE_H__
