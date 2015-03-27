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
    static Scene* createScene();   
    virtual bool init();  
	CREATE_FUNC(GameScene);

	bool initializeGame();
	void update(float delta);	
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	void gameOver();
	void mainMenu();
	void pauseGame();	
	void updateTimer(float dt);
	
private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	int spawnSegmentTimer;
	PhysicsWorld* m_pSceneWorld;			
	HUD* m_HudLayer;
	Parallax* m_pParallax;
	Layer* gamePlayLayer;	
	Player* m_pPlayer;
	CollectableFactory* m_pCollectableFactory;
	SpawnManager* m_pSpawnManager;
	Enemy m_enemey;	
	bool m_bPaused;

	float m_nGameTime;
};

#endif // __GAMESCENE_SCENE_H__
