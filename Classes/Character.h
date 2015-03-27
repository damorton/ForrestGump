/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Character.h

	Description: Character is an abstract class used for creating players and enemies in the game providing
	a set of functions that are essential for characters in the game.
*/
#ifndef CHARACTER_H_
#define CHARACTER_H_

class Character
{
public:
	typedef enum { PLAYER, ENEMY, BOSS, ITEM } EGameOjectType;
	typedef enum { ALIVE, DEAD } ECharacterState;
	virtual ~Character(){};
	virtual bool init() = 0;	
	virtual EGameOjectType getType() = 0;
	virtual void setType(EGameOjectType type) = 0;
	virtual void setState(ECharacterState state) = 0;
protected:
	EGameOjectType m_eType;	
	ECharacterState m_eState;
};

#endif