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
	bool onContactBegin(cocos2d::PhysicsContact& contact);
	void gameOver();
	void pauseGame();
	void resumeGame(cocos2d::Ref *pSender);
	void mainGame(cocos2d::Ref *pSender);
	void exit(cocos2d::Ref *pSender);

	//PAUSE MENU
	//pausedSprite is simply an image that literally says ‘Paused’
	CCSprite *pausedSprite;
	//pausedMenu is the CCMenu that contains buttons for quit, restart and resume.
	CCMenu *pausedMenu;
	//paused is a variable that tracks when the game is or isn’t paused.
	bool paused;

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
