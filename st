[1mdiff --git a/Classes/GameScene.cpp b/Classes/GameScene.cpp[m
[1mindex afe5adc..728a5e6 100644[m
[1m--- a/Classes/GameScene.cpp[m
[1m+++ b/Classes/GameScene.cpp[m
[36m@@ -16,6 +16,7 @@[m [mScene* GameScene::createScene()[m
 	auto scene = Scene::createWithPhysics();	[m
 	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); // draw debug lines around objects in the world	[m
 	scene->getPhysicsWorld()->setUpdateRate(0.3f);[m
[32m+[m
 	// 'layer' is an autorelease object[m
 	auto layer = GameScene::create();[m
 	layer->SetPhysicsWorld(scene->getPhysicsWorld()); // set the layers physics[m
[36m@@ -36,7 +37,7 @@[m [mbool GameScene::init()[m
 	{[m
 		return false;[m
 	}[m
[31m-	[m
[32m+[m
 	Size visibleSize = Director::getInstance()->getVisibleSize();[m
 	Vec2 origin = Director::getInstance()->getVisibleOrigin();[m
 [m
[36m@@ -50,34 +51,39 @@[m [mbool GameScene::init()[m
 [m
 	// HUD layer[m
 	m_cHud = HUD::create();[m
[31m-	this->addChild(m_cHud, 1, "hudLayer");[m
[32m+[m	[32mthis->addChild(m_cHud, 1, "hudLayer");[m[41m	[m
[32m+[m
[32m+[m[32m//	gamePlayLayer->addChild(m_Parallax->getInstance()->m_pSpriteBackgroundFirst, 1);[m
[32m+[m[32m//	gamePlayLayer->addChild(Parallax::getInstance()->m_pSpriteBackgroundFirst1, 1);[m
 [m
 	[m
 	// background 1 - Clouds and Floor moving[m
[31m-	m_bckFirst = CCSprite::create("background/backgroundFirst.png"); [m
[31m-	m_bckFirst1 = CCSprite::create("background/backgroundFirst.png"); [m
[31m-	m_bckFirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[31m-	m_bckFirst1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));	[m
[31m-	gamePlayLayer->addChild(m_bckFirst, 1); // add child[m
[31m-	gamePlayLayer->addChild(m_bckFirst1, 1); // add child[m
[32m+[m	[32mm_pSpriteBackgroundFirst = CCSprite::create("background/backgroundFirst.png");[m[41m [m
[32m+[m	[32mm_pSpriteBackgroundFirst1 = CCSprite::create("background/backgroundFirst.png");[m[41m [m
[32m+[m	[32mm_pSpriteBackgroundFirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mm_pSpriteBackgroundFirst1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m[41m	[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundFirst, 1); // add child[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundFirst1, 1); // add child[m
 [m
 [m
 	// background 2 - Mountains[m
[31m-	m_bckSecond = CCSprite::create("background/backgroundSecond.png");[m
[31m-	m_bckSecond1 = CCSprite::create("background/backgroundSecond.png");[m
[31m-	m_bckSecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[31m-	m_bckSecond1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[31m-	gamePlayLayer->addChild(m_bckSecond, -1); // add child[m
[31m-	gamePlayLayer->addChild(m_bckSecond1, -1); // add child[m
[32m+[m	[32mm_pSpriteBackgroundSecond = CCSprite::create("background/backgroundSecond.png");[m
[32m+[m	[32mm_pSpriteBackgroundSecond1 = CCSprite::create("background/backgroundSecond.png");[m
[32m+[m	[32mm_pSpriteBackgroundSecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mm_pSpriteBackgroundSecond1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundSecond, -1); // add child[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundSecond1, -1); // add child[m
 [m
 [m
 	// background 3	- Clounds, Sun and Far Mountains[m
[31m-	m_bckThird = CCSprite::create("background/backgroundThird.png");[m
[31m-	m_bckThird1 = CCSprite::create("background/backgroundThird.png");[m
[31m-	m_bckThird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[31m-	m_bckThird1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[31m-	gamePlayLayer->addChild(m_bckThird, -2); // add child[m
[31m-	gamePlayLayer->addChild(m_bckThird1, -2); // add child[m
[32m+[m	[32mm_pSpriteBackgroundThird = CCSprite::create("background/backgroundThird.png");[m
[32m+[m	[32mm_pSpriteBackgroundThird1 = CCSprite::create("background/backgroundThird.png");[m
[32m+[m	[32mm_pSpriteBackgroundThird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mm_pSpriteBackgroundThird1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundThird, -2); // add child[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundThird1, -2); // add child[m
[32m+[m[41m	[m
[32m+[m
 [m
 	// add floorSprite to game scene[m
 	auto floorSprite = Sprite::create("foreground/floorSprite.png");[m
[36m@@ -121,7 +127,7 @@[m [mbool GameScene::init()[m
 	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);	[m
 	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);[m
 			[m
[31m-	m_fSpeed = 5.0f;[m
[32m+[m	[32m//m_fSpeed = 5.0f;[m
 [m
 	// call the schedule update in order to run this layers update function[m
 	this->scheduleUpdate();[m
[36m@@ -133,11 +139,11 @@[m [mvoid GameScene::update(float delta)[m
 	CCLOG("-------------GAME LOOP START--------------");	[m
 [m
 	WorldManager::getInstance()->getPlayer()->update();[m
[31m-	m_cHud->updateScore();[m
[32m+[m	[32mm_cHud->updateScore();[m[41m	[m
 [m
[31m-	m_Parallax->scrollBackground(m_bckFirst, m_bckFirst1, m_fSpeed);[m
[31m-	m_Parallax->scrollBackground(m_bckSecond, m_bckSecond1, (m_fSpeed / 2));[m
[31m-	m_Parallax->scrollBackground(m_bckThird, m_bckThird1, ((m_fSpeed / 5) - 0.8));	[m
[32m+[m	[32mm_pParallax->scrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);[m
[32m+[m	[32mm_pParallax->scrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, (m_fSpeed / 2));[m
[32m+[m	[32mm_pParallax->scrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, ((m_fSpeed / 5) - 0.8));[m[41m	[m
 	[m
 	CCLOG("-------------GAME LOOP END--------------");[m
 }[m
[1mdiff --git a/Classes/GameScene.h b/Classes/GameScene.h[m
[1mindex a75fd1e..452297b 100644[m
[1m--- a/Classes/GameScene.h[m
[1m+++ b/Classes/GameScene.h[m
[36m@@ -49,25 +49,24 @@[m [mpublic:[m
 	*/[m
 	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);[m
 	//void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event * event);[m
[31m-	//void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);	[m
[31m-	[m
[32m+[m	[32m//void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event * event);[m[41m		[m
 [m
 private:[m
 	void SetPhysicsWorld(PhysicsWorld *world) { m_pSceneWorld = world; };[m
 	PhysicsWorld* m_pSceneWorld;[m
[31m-[m
[32m+[m[41m	[m
 	// layers	[m
 	Layer* gamePlayLayer;[m
 	HUD* m_cHud;[m
[31m-	Parallax* m_Parallax;[m
[32m+[m	[32mParallax* m_pParallax;[m
 [m
 	// sprites[m
[31m-	Sprite* m_bckFirst;[m
[31m-	Sprite* m_bckFirst1;[m
[31m-	Sprite* m_bckSecond;[m
[31m-	Sprite* m_bckSecond1;[m
[31m-	Sprite* m_bckThird;[m
[31m-	Sprite* m_bckThird1;[m
[32m+[m	[32mSprite* m_pSpriteBackgroundFirst;[m
[32m+[m	[32mSprite* m_pSpriteBackgroundFirst1;[m
[32m+[m	[32mSprite* m_pSpriteBackgroundSecond;[m
[32m+[m	[32mSprite* m_pSpriteBackgroundSecond1;[m
[32m+[m	[32mSprite* m_pSpriteBackgroundThird;[m
[32m+[m	[32mSprite* m_pSpriteBackgroundThird1;[m
 [m
 	// variables[m
 	float m_fSpeed;[m
[1mdiff --git a/Classes/Parallax.cpp b/Classes/Parallax.cpp[m
[1mindex 1ed46f6..bdfe2d3 100644[m
[1m--- a/Classes/Parallax.cpp[m
[1m+++ b/Classes/Parallax.cpp[m
[36m@@ -2,22 +2,64 @@[m
 [m
 USING_NS_CC;[m
 [m
[31m-Parallax* Parallax::m_pInstance = 0;[m
[32m+[m[32mParallax* Parallax::m_spInstance = 0;[m
 [m
 Parallax* Parallax::getInstance()[m
 {[m
[31m-	if (m_pInstance == 0)[m
[32m+[m	[32mif (m_spInstance == 0)[m
 	{[m
[31m-		m_pInstance = new Parallax();[m
[32m+[m		[32mm_spInstance = new Parallax();[m[41m	[m
 	}[m
[31m-	return m_pInstance;[m
[32m+[m
[32m+[m	[32mreturn m_spInstance;[m
 }[m
 [m
[31m-bool Parallax::init()[m
[32m+[m[32m/*[m
[32m+[m[32mParallax* Parallax::create2()[m
 {[m
[32m+[m	[32m// background play layer[m
[32m+[m	[32mbackgroundLayer = Layer::create();[m
[32m+[m
[32m+[m	[32mSize visibleSize = Director::getInstance()->getVisibleSize();[m
[32m+[m	[32mVec2 origin = Director::getInstance()->getVisibleOrigin();[m
[32m+[m[41m	[m
[32m+[m	[32m// background 1 - Clouds and Floor moving[m
[32m+[m	[32mm_pSpriteBackgroundFirst = CCSprite::create("background/backgroundFirst.png");[m
[32m+[m	[32mm_pSpriteBackgroundFirst1 = CCSprite::create("background/backgroundFirst.png");[m
[32m+[m	[32mm_pSpriteBackgroundFirst->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mm_pSpriteBackgroundFirst1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mbackgroundLayer->addChild(m_pSpriteBackgroundFirst, 1); // add child[m
[32m+[m	[32mbackgroundLayer->addChild(m_pSpriteBackgroundFirst1, 1); // add child[m
[32m+[m
[32m+[m[41m	[m
[32m+[m	[32m// background 2 - Mountains[m
[32m+[m	[32mm_pSpriteBackgroundSecond = CCSprite::create("background/backgroundSecond.png");[m
[32m+[m	[32mm_pSpriteBackgroundSecond1 = CCSprite::create("background/backgroundSecond.png");[m
[32m+[m	[32mm_pSpriteBackgroundSecond->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mm_pSpriteBackgroundSecond1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundSecond, -1); // add child[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundSecond1, -1); // add child[m
[32m+[m
[32m+[m
[32m+[m	[32m// background 3	- Clounds, Sun and Far Mountains[m
[32m+[m	[32mm_pSpriteBackgroundThird = CCSprite::create("background/backgroundThird.png");[m
[32m+[m	[32mm_pSpriteBackgroundThird1 = CCSprite::create("background/backgroundThird.png");[m
[32m+[m	[32mm_pSpriteBackgroundThird->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mm_pSpriteBackgroundThird1->setPosition(Vec2(visibleSize.width + visibleSize.width / 2, visibleSize.height / 2));[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundThird, -2); // add child[m
[32m+[m	[32mgamePlayLayer->addChild(m_pSpriteBackgroundThird1, -2); // add child[m
[32m+[m[41m	[m
 	return true;[m
 }[m
 [m
[32m+[m[32mvoid Parallax::updateBackground()[m
[32m+[m[32m{[m
[32m+[m	[32mm_fSpeed = 5.0f;[m
[32m+[m	[32mscrollBackground(m_pSpriteBackgroundFirst, m_pSpriteBackgroundFirst1, m_fSpeed);[m
[32m+[m	[32mscrollBackground(m_pSpriteBackgroundSecond, m_pSpriteBackgroundSecond1, (m_fSpeed / 2));[m
[32m+[m	[32mscrollBackground(m_pSpriteBackgroundThird, m_pSpriteBackgroundThird1, ((m_fSpeed / 5) - 0.8));[m
[32m+[m[32m}[m
[32m+[m[32m*/[m
 void Parallax::scrollBackground(Sprite* bck1, Sprite* bck2, float speed)[m
 {[m
 	bck1->setPosition(Vec2(bck1->getPosition().x - speed, bck1->getPosition().y));[m
[1mdiff --git a/Classes/Parallax.h b/Classes/Parallax.h[m
[1mindex e0f58b4..7071780 100644[m
[1m--- a/Classes/Parallax.h[m
[1m+++ b/Classes/Parallax.h[m
[36m@@ -2,6 +2,7 @@[m
 #define __PARALLAX_H__[m
 [m
 #include "cocos2d.h"[m
[32m+[m[32m#include "GameScene.h"[m
 [m
 	USING_NS_CC;[m
 [m
[36m@@ -12,14 +13,34 @@[m [mclass Parallax[m
 		Initialize the Parallax class[m
 		*/[m
 		virtual bool init();[m
[31m-[m
[31m-		static Parallax* getInstance();[m
[32m+[m[41m		[m
[32m+[m		[32mstatic Parallax* getInstance();[m[41m	[m
 [m
 		// Update my background scrolling[m
 		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);[m
 [m
[32m+[m
[32m+[m		[32m/*[m
[32m+[m		[32m// Call the scroll function passing the background images[m
[32m+[m		[32mvoid updateBackground();[m
[32m+[m
[32m+[m		[32m// sprites[m
[32m+[m		[32mSprite* m_pSpriteBackgroundFirst;[m
[32m+[m		[32mSprite* m_pSpriteBackgroundFirst1;[m
[32m+[m		[32mSprite* m_pSpriteBackgroundSecond;[m
[32m+[m		[32mSprite* m_pSpriteBackgroundSecond1;[m
[32m+[m		[32mSprite* m_pSpriteBackgroundThird;[m
[32m+[m		[32mSprite* m_pSpriteBackgroundThird1;[m
[32m+[m
[32m+[m		[32m// variables[m
[32m+[m		[32mfloat m_fSpeed;[m
[32m+[m		[32m*/[m
[32m+[m		[32m//GameScene* gs;[m
[32m+[m
 private:[m
[31m-	static Parallax* m_pInstance;[m
[32m+[m	[32mstatic Parallax* m_spInstance;[m
[32m+[m	[32m// layers[m[41m	[m
[32m+[m	[32mLayer* backgroundLayer;[m
 };[m
 [m
 #endif // __PARALLAX_H__[m
