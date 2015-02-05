#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h" // inherit from Character
#include <iostream>

class Player : public Character
{
protected:
	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING } EPlayerState; // player state
	EPlayerState m_ePlayerState; // Player state
	float m_fPlayerXPos;
public:
	Player(){ this->init(); }; // constructor
	Player(std::string name); // set player name
	~Player(){ this->cleanUp(); }; // deconstructor
	virtual bool init(); // initialization
	void jump();
	void moveLeft();
	void moveRight();
	void Player::touch(const Point& location);
	void duck(){ std::cout << "Player ducking" << std::endl; }; // duck
	void boost(){ std::cout << "Player boosting" << std::endl; }; // boost
	virtual void update(); // update Player
	virtual void cleanUp(); // delete Player object
	
	// getters
	int getState(){ return m_ePlayerState; };

	// setters 
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };
};

#endif