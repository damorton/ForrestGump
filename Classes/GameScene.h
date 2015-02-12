#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "SegmentManager.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:    
    static cocos2d::Scene* createScene();   
    virtual bool init();  
	void initializeGame();
	void onEnterTransitionDidFinish();
	void update(float delta);	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);	
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	CREATE_FUNC(GameScene);	
private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	PhysicsWorld* m_pSceneWorld;	
	Sprite* backgroundA;
	Sprite* backgroundB;
	int spawnSegmentTimer;
	SegmentManager* m_pSegmentManager;
};

#endif // __GAMESCENE_SCENE_H__
