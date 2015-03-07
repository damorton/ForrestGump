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

<<<<<<< HEAD
#define PADDING 10
=======
// World
>>>>>>> 7637a88db55320ba18c3097020f29a5428389c8b
#define GRAVITATIONAL_FORCE Vec2(0, -300)
#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define SCREEN_ORIGIN (Director::getInstance()->getVisibleOrigin())

// Movement speeds
#define WORLD_MOVEMENT_SPEED (WorldManager::getInstance()->getGameWorldSpeed())
#define ENEMY_MOVEMENT_SPEED (WorldManager::getInstance()->getEnemyMovementSpeed())

// Scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// Player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 7) * 1)
#define JUMP_SPEED 0.75F
#define PLAYER_JUMP_VEL Vec2(0.0f, 80000.0f)
#define MAX_NO_OF_JUMPS 2
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height * .75)

// Enemies
#define ENEMY_SPAWN_COUNT 5

// Labels
#define LABEL_FONT "fonts/go3v2.ttf"
#define LABEL_FONT_SIZE (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / Director::getInstance()->getVisibleSize().width * 32)
#define PADDING 10

#endif 
