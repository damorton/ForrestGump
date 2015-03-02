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
#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define SCREEN_ORIGIN (Director::getInstance()->getVisibleOrigin())

// Sprites; coins, items, powerups
#define SPRITE_MOVEMENT_SPEED 0.005f

// scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 3) * 1)
#define JUMP_SPEED 0.75F
#define MAX_NO_OF_JUMPS 2
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height * .75)

// enemy spawns
#define ENEMY_SPAWN_FREQ_LEVEL_1 0.00929
#define ENEMY_SPAWN_FREQ_LEVEL_2 0.00629
#define ENEMY_SPAWN_FREQ_LEVEL_3 0.00429f
#define ENEMY_SPAWN_FREQ_LEVEL_4 0.00229f
#define ENEMY_SPAWN_FREQ_LEVEL_5 0.00109f
#define ENEMY_SPAWN_FREQ_LEVEL_6 0.00099f
#define ENEMY_SPAWN_FREQ_LEVEL_7 0.00088f
#define ENEMY_MOVEMENT_SPEED 0.008f

#define LABEL_FONT "fonts/go3v2.ttf"
#define LABEL_FONT_SIZE (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / Director::getInstance()->getVisibleSize().width * 32)

// spawn manager
#define ENEMY_SPAWN_COUNT 5

#endif // DEFINITIONS_H__
