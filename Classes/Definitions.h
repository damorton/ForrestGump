#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__


#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)

typedef enum {
	TAG_GAME_LAYER,
	TAG_HUD,
	TAG_GAME_SCENE,
	TAG_PAUSE,
	TAG_GAMEOVER,
	TAG_SEGMENT,
	TAG_SEGMENT_MANAGER,
	TAG_HUD_MENU,
} tags;

// segments
#define SEGMENT_MOVEMENT_SPEED 0.007f
#define SEGMENT_START_POS (Vec2(VISIBLE_SIZE_WIDTH + VISIBLE_SIZE_WIDTH / 2, 0))
#define SEGMENT_SPAWN_TIME 100

// scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// fonts
#define FONT_SIZE ((Director::getInstance()->getVisibleSize().width / 1920) * 100)
#define PADDING 10

// player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 3) * 1)
#define JUMP_SPEED 0.75F
#define NO_OF_JUMPS 1
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height / 2)

// floor
#define FLOOR_SPRITE_TOP (WorldManager::getInstance()->getFloorSprite()->getPositionY() + playerSprite->getContentSize().height / 1.20))

// enemy spawns
#define ENEMY_SPAWN_FREQ 0.002
#define	ENEMY_GAP 20
#define	UPPER_SCRENE_ENEMY_THRESHOLD 0.75
#define	LOWER_SCRENE_ENEMY_THRESHOLD 0.25
#define ENEMY_MOVEMENT_SPEED 0.005
#define SCROLL_SPEED 0.005

#endif // DEFINITIONS_H__
