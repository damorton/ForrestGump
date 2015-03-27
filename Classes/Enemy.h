/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Enemy.h

Description: Class responsable for create the enemies.
There are two mains types of enemies, Flight enemies and Ground enemies.
This class is also responsable for animate themselves.

*/

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite, public Character
{
public:		

	/* @brief Creates the Enemy */
	static Enemy* create(const std::string& filename);
	
	/* @brief Enemy deconstructor */
	virtual ~Enemy(){ this->enemyCleanUp(); };

	/* @brief Init function that Initialize the enemy class */
	virtual bool init(); 	

	/* @brief TODO : Implement clean up function */
	virtual void enemyCleanUp(); 

	/* @brief TODO : Implement Artificial Intelligence */
	void runAI(); 

	/* @brief getType function to specify that any class that inherits from this has to implement this function */
	EGameOjectType getType(){ return m_eType; };

	/* @brief TODO : Implement getState to handle with Enemy states */
	int getState(){ return m_eState; };

	/* @brief set type function to specify that any class that inherits from this has to implement this function
	and set its type */
	void setType(EGameOjectType type){ m_eType = type; };

	/* @brief TODO : Implement setState to set Enemy states */
	void setState(ECharacterState state){ m_eState = state; };

	/* @brief getRandomSpeed return a random value to be used as speed movement */
	void getRandomSpeed();
	
	/* @brief pointer to the random speed value */
	int getSpeed(){ return m_nSpeed; };
	
	/* ANIMATION */

	/* @brief get Enemy by name and animate */
	void animateEnemy();

	/* @brief Create and execute the enemy animation  */
	void getAnimationWithFrames(char* enemyAnimation, int frames);

	/* @brief pointer to the Animate object */
	Animate* animate;

	/* @brief random speed value */
	int m_nSpeed;

};

#endif