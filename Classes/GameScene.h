#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "CollectableFactory.h"
#include "HUD.h"
#include "Parallax.h"
#include "AnimationMoves.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Enemy.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:    
    static cocos2d::Scene* createScene();   
    virtual bool init();  
	virtual ~GameScene(){ this->cleanup(); };
	void cleanup();
	bool initializeGame();
	void update(float delta);	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);	
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void pause();
	CREATE_FUNC(GameScene);
private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	PhysicsWorld* m_pSceneWorld;		
	CollectableFactory* m_pCollectableFactory;
	HUD* m_HudLayer;
	Parallax* m_pParallax;
	Layer* gamePlayLayer;
	SpawnManager* m_pSpawnManager;
	Enemy m_enemey;	
};

#endif // __GAMESCENE_SCENE_H__
