#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "SegmentManager.h"
#include "HUD.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:    
    static cocos2d::Scene* createScene();   
    virtual bool init();  
	void initializeGame();
	void update(float delta);	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);	
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void pause(cocos2d::Ref *pSender);
	CREATE_FUNC(GameScene);
private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	PhysicsWorld* m_pSceneWorld;	
	Sprite* backgroundA;
	Sprite* backgroundB;
	int spawnSegmentTimer;
	SegmentManager* m_pSegmentManager;
	HUD* m_HudLayer;
};

#endif // __GAMESCENE_SCENE_H__
