#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "SegmentManager.h"
#include "HUD.h"
#include "Parallax.h"
#include "AnimationMoves.h"
#include "Player.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:    
    static cocos2d::Scene* createScene();   
    virtual bool init();  
	bool initializeGame();
	void update(float delta);	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);	
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void pause();
	CREATE_FUNC(GameScene);
private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	PhysicsWorld* m_pSceneWorld;	
	Sprite* backgroundA;
	Sprite* backgroundB;
	int spawnSegmentTimer;
	SegmentManager* m_pSegmentManager;
	HUD* m_HudLayer;
	Parallax* m_pParallax;
	Layer* gamePlayLayer;

	/*

	// sprites
	Sprite* m_pSpriteBackgroundFirst;
	Sprite* m_pSpriteBackgroundFirst1;
	Sprite* m_pSpriteBackgroundSecond;
	Sprite* m_pSpriteBackgroundSecond1;
	Sprite* m_pSpriteBackgroundThird;
	Sprite* m_pSpriteBackgroundThird1;
	*/

	// variables
	float m_fSpeed;
};

#endif // __GAMESCENE_SCENE_H__
