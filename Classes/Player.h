#ifndef PLAYER_H_
#define	PLAYER_H_

//#include "Character.h" // inherit from Character
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class Player : public Sprite
{
protected:
	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING } EPlayerState; // player state
	EPlayerState m_ePlayerState; // Player state

public:		
	static Player* create(const std::string& filename);
	virtual bool init(); // initialization
	void jump();	
	void cleanUp(); // delete Player object
	
	// getters
	int getState(){ return m_ePlayerState; };

	// setters 
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };

	CREATE_FUNC(Player);
};

#endif