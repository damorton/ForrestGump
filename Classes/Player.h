#ifndef PLAYER_H_
#define	PLAYER_H_

//#include "Character.h" // inherit from Character
#include "cocos2d.h"
#include <iostream>

class Player : public cocos2d::Sprite
{
protected:
	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING } EPlayerState; // player state
	EPlayerState m_ePlayerState; // Player state
	float m_fPlayerXPos;

public:		
	virtual bool init(); // initialization
	void jump();
	void moveLeft();
	void moveRight();
	//void Player::touch(const Point& location);
	void duck(){ std::cout << "Player ducking" << std::endl; }; // duck
	void boost(){ std::cout << "Player boosting" << std::endl; }; // boost

	void update(float) override;
	
	virtual void cleanUp(); // delete Player object
	
	// getters
	int getState(){ return m_ePlayerState; };

	// setters 
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };

	CREATE_FUNC(Player);
};

#endif