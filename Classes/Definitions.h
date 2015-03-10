#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__

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

// World
#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define SCREEN_ORIGIN (Director::getInstance()->getVisibleOrigin())
#define GAME_SPEED_INC (float)1.05
#define GAME_SPEED_DEC (float)1.05
#define GRAVITATIONAL_FORCE Vec2(0, -500)
#define WORLD_MOVEMENT_SPEED 6.0f
#define ENEMY_MOVEMENT_SPEED 7.0f

// Scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// Player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 10) * 2)
#define PLAYER_JUMP_VEL Vec2(0.0f, 500.0f)
#define MAX_NO_OF_JUMPS 1
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height * .75)

// Labels
#define LABEL_FONT "fonts/go3v2.ttf"
#define LABEL_FONT_SIZE (Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / Director::getInstance()->getVisibleSize().width * 32)
#define PADDING 10

#endif 
