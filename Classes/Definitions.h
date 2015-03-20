#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__

#include "cocos2d.h"

#define XMLDOC "game.xml"

typedef enum {
	TAG_GAME_LAYER,
	TAG_HUD,
	TAG_GAME_SCENE,
	TAG_GAMEOVER,
	TAG_SEGMENT,
	TAG_SEGMENT_MANAGER,
	TAG_HUD_MENU,
	TAG_COIN,
	TAG_ITEM,
	TAG_BOOSTER,
	TAG_FOOD,
} tags;


#define PADDING 10

#define DISTANCE_VALUE_LABEL_COLOR 255, 0, 127 

// World
#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define SCREEN_ORIGIN (Director::getInstance()->getVisibleOrigin())
#define GAME_SPEED_INC (float)1.05
#define GAME_SPEED_DEC (float)1.05
#define GRAVITATIONAL_FORCE Vec2(0, -200)
#define WORLD_MOVEMENT_SPEED 3.0f
#define ENEMY_MOVEMENT_SPEED 4.0f

// Scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// Player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 10) * 2)
#define PLAYER_JUMP_VEL Vec2(0.0f, 200.0f)
#define MAX_NO_OF_JUMPS 1
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height * .75)

// Labels
#define LABEL_FONT "fonts/go3v2.ttf"
#define LABEL_FONT_SIZE (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / cocos2d::Director::getInstance()->getVisibleSize().width * 16)
#define PADDING 10

// New design resolution
#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_1920X1080  2
#define DESIGN_RESOLUTION_2048X1536  3

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_480X320

typedef struct tagResource
{
	cocos2d::Size size;
	char directory[100];
}Resource;

static Resource smallResource = { cocos2d::Size(480, 320), "resolutions/small" };
static Resource mediumResource = { cocos2d::Size(1024, 768), "resolutions/medium" };
static Resource largeResource = { cocos2d::Size(2048, 1536), "resolutions/large" };

#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::Size designResolutionSize = cocos2d::Size(2048, 1536);
#else
#error unknown target design resolution!
#endif

#endif 
