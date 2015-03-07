#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "CollectableFactory.h"
#include "HUD.h"
#include "Parallax.h"
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
	void gameOver();
	//void addScreenShake();
	CREATE_FUNC(GameScene);
	
private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	int spawnSegmentTimer;

	PhysicsWorld* m_pSceneWorld;			
	HUD* m_HudLayer;
	Parallax* m_pParallax;
	Layer* gamePlayLayer;
	Player* playerSprite;
	CollectableFactory* m_pCollectableFactory;
	SpawnManager* m_pSpawnManager;
	Enemy m_enemey;	
};

#endif // __GAMESCENE_SCENE_H__
