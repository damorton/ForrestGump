#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "Maze.h"
#include "HUD.h"

USING_NS_CC;

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

	// touch controls 
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	//void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	//void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);	

private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };

	PhysicsWorld* m_pSceneWorld;

	Layer* gamePlayLayer;
	HUD* m_cHud;
};

#endif // __GAMESCENE_SCENE_H__
