#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__

#define PADDING 10
#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define SIZE (Director::getInstance()->getVisibleSize())
#define ORIGIN (Director::getInstance()->getVisibleOrigin())

// hud
#define LABEL_POSITION_X (ORIGIN + PADDING + )
#define VALUE_LABEL_POSITION_X (VDirector::getInstance()->getVisibleSize().width * 0.25)

typedef enum {
	TAG_GAME_LAYER,
	TAG_HUD,
	TAG_GAME_SCENE,
	TAG_PAUSE,
	TAG_GAMEOVER,
	TAG_SEGMENT,
	TAG_SEGMENT_MANAGER,
	TAG_HUD_MENU,
	TAG_COIN,
	TAG_ITEM,
	TAG_BOOSTER,
	TAG_FOOD,
} tags;

// Sprites; coins, items, powerups
#define SPRITE_MOVEMENT_SPEED 0.008f

// scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// fonts
#define FONT_SIZE ((Director::getInstance()->getVisibleSize().width / 1920) * 100)

// player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 3) * 1)
#define JUMP_SPEED 0.75F
#define NO_OF_JUMPS 1
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height * .75)

// enemy spawns
#define ENEMY_SPAWN_FREQ 0.002
#define	ENEMY_GAP 20
#define	UPPER_SCRENE_ENEMY_THRESHOLD 0.75
#define	LOWER_SCRENE_ENEMY_THRESHOLD 0.25
#define ENEMY_MOVEMENT_SPEED 0.008f

#define LABEL_FONT "fonts/go3v2.ttf"
#define VALUE_FONT "fonts/Roboto-Light.ttf"

#endif // DEFINITIONS_H__
