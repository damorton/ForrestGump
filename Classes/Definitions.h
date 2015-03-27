/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

Definitions.h

Description: Here we define common value within the game. This allows us
to write cleaner code as we can define values for later use.
*/

#ifndef DEFINITIONS_H__
#define DEFINITIONS_H__

// Includes
#include "cocos2d.h"
USING_NS_CC;

// Defines
#define XMLDOC "game.xml"
#define DISTANCE_VALUE_LABEL_COLOR 255, 0, 127 
#define CONTENT_SCALE_FACTOR cocos2d::Director::getInstance()->getContentScaleFactor()

// World
#define VISIBLE_SIZE_WIDTH (Director::getInstance()->getVisibleSize().width)
#define VISIBLE_SIZE_HEIGHT (Director::getInstance()->getVisibleSize().height)
#define SCREEN_ORIGIN (Director::getInstance()->getVisibleOrigin())
#define GAME_SPEED_INC 0.25
#define GAME_SPEED_DEC GAME_SPEED_INC
#define WORLD_MOVEMENT_SPEED 2.0
#define ENEMY_MOVEMENT_SPEED 3.0
#define MAX_GAME_SPEED 7.0

// Scenes
#define DISPLY_TIME_SPLASH_SCENCE 2
#define TRANSITION_TIME 0.5

// Player
#define PLAYER_POSITION_IN_WINDOW ((Director::getInstance()->getVisibleSize().width / 10) * 2)
#define MAX_PLAYER_VEL (VISIBLE_SIZE_HEIGHT * .70)
#define PLAYER_JUMP_VEL Vec2(0.0f, MAX_PLAYER_VEL)
#define GRAVITATIONAL_FORCE Vec2(0, -MAX_PLAYER_VEL)
#define MAX_NO_OF_JUMPS 1
#define JUMP_HEIGHT (Director::getInstance()->getVisibleSize().height * .75)

// Labels
#define LABEL_FONT "fonts/go3v2.ttf"
#define LABEL_FONT_ROBOTO "Roboto-Light.ttf"
//#define LABEL_FONT_SIZE (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / cocos2d::Director::getInstance()->getVisibleSize().width * 16)
#define LABEL_FONT_SIZE 16
#define PADDING 10

// Enums
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

// Structs
typedef struct tagResource
{
	cocos2d::Size size;
	char directory[100];
}Resource;


// Design resolutions setup
static Resource smallResource = { cocos2d::Size(480, 320), "resolutions/small" };
static Resource mediumResource = { cocos2d::Size(1024, 768), "resolutions/medium" };
static Resource largeResource = { cocos2d::Size(2048, 1536), "resolutions/large" };

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);

#endif 
