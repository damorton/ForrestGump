#ifndef POPUP_H__
#define POPUP_H__

#include "Definitions.h"

class Popup : public cocos2d::Sprite
{
	cocos2d::CCMenu *menu;
public:
	bool init();
	static Popup* createPopup();
	void show(bool shouldShow, bool);
};

#endif // __POPUP_SPRITE_H__