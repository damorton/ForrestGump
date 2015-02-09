#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
#include "HUD.h"
#include "Maze.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	// update the game scene
	void update(float delta);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
		
	/*
		Pause button creates a new pause scene and pushes it over the game scene

		@param cocos2d::Ref *pSender pointer used by the engine
	*/
	void Pause(Ref *pSender);

	/*
		EndGame button creates a new game game scene and replaces the game scene

		@param cocos2d::Ref *pSender pointer used by the engine
	*/
	void EndGame(Ref *pSender);

	/*
		Passing the location the user touched into the player function to check for a jump

		@param Touch coordinate
		@param Event event type

		@return bool touch registered
	*/
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
	//void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);
	//void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);	

private:
	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };
	PhysicsWorld* m_pSceneWorld;

	// layers	
	Layer* gamePlayLayer;
	HUD* m_cHud;
	Maze* mazeLayer;

	// sprites
	Sprite* backgroundA;
	Sprite* backgroundB;

	// variables
	float speed;
};

#endif // __GAMESCENE_SCENE_H__
