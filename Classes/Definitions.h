#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__

typedef enum {
	TAG_GAME_LAYER,
	TAG_HUD,
	TAG_GAME_SCENE,
	TAG_PAUSE,
	TAG_GAMEOVER,
	TAG_SEGMENT,
	TAG_SEGMENT_MANAGER,
} tags;

#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define SEGMENT_MOVEMENT_SPEED 0.007f

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

#endif // DEFINITIONS_H__
