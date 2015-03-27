/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Enemy.h

	Description: Class responsable for create the enemies. There are two mains types of enemies, Flight enemies and Ground enemies.
	This class is also responsable for animate themselves.

*/
#ifndef ENEMY_H_
#define ENEMY_H_

// Includes
#include "Definitions.h"
#include "Character.h"

class Enemy : public Sprite, public Character
{
public:		

	// Creates the Enemy
	static Enemy* create(const std::string& filename);
	
	// Enemy deconstructor
	virtual ~Enemy(){ this->enemyCleanUp(); };

	// Init function that Initialize the enemy class
	virtual bool init(); 	

	// TODO : Implement clean up function
	virtual void enemyCleanUp(); 

	// TODO : Implement Artificial Intelligence
	void runAI(); 

	// getType function to specify that any class that inherits from this has to implement this function
	EGameOjectType getType(){ return m_eType; };

	// TODO : Implement getState to handle with Enemy states
	int getState(){ return m_eState; };

	// setType function to specify that any class that inherits from this has to implement this function and set its type
	void setType(EGameOjectType type){ m_eType = type; };

	// TODO : Implement setState to set Enemy states
	void setState(ECharacterState state){ m_eState = state; };

	// getRandomSpeed return a random value to be used as speed movement
	void getRandomSpeed();
	
	// Pointer to the random speed value 
	int getSpeed(){ return m_nSpeed; };
	
	// Get Enemy by name and animate
	void animateEnemy();

	// Create and execute the enemy animation
	void getAnimationWithFrames(char* enemyAnimation, int frames);

	// Pointer to the Animate object
	Animate* animate;

	// Random speed value 
	int m_nSpeed;

};

#endif