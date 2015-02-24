#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
	static void mainMenu();

	void playGame(Ref *pSender);
	void leaderboard(Ref *pSender);
	void settings(Ref *pSender);		
	CREATE_FUNC(MainMenu);

};

#endif // __MAINMENU_SCENE_H__
