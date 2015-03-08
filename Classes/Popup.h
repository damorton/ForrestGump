#ifndef POPUP_H__
#define POPUP_H__

#include "cocos2d.h"

class Popup : public cocos2d::Sprite
{
	cocos2d::CCMenu *menu;
public:
	bool init();
	static Popup* createPopup();
	void show(bool shouldShow);
	int cont;

	void pauseGame();
	void mainMenu();
};

#endif // __POPUP_SPRITE_H__