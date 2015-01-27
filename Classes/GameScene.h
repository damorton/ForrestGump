#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__
#define FONT_SIZE ((visibleSize.width / 1920) * 100)
#include "cocos2d.h"

class GameManager;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	
	// update the game scene
	void update(float) override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
		
	void Pause(Ref *pSender);
	void EndGame(Ref *pSender);
	
};

#endif // __GAMESCENE_SCENE_H__
