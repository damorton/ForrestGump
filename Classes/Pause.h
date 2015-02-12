#ifndef PAUSE_H__
#define PAUSE_H__

#include "cocos2d.h"

class Pause : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	cocos2d::Sprite *mySprite;

	void resume(Ref *pSender);
	void mainMenu(Ref *pSender);
	void exit(Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Pause);
};

#endif // __PAUSE_SCENE_H__