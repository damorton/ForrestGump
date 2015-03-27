/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Shield.h

	Description: Creates a shield object which inherits from powerUp.h and sprite

*/
#ifndef SHIELD_H_
#define SHIELD_H_

// Includes
#include "Definitions.h"
#include "PowerUps.h"

class Shield : public Sprite, public PowerUps
{
public:
	// Create
	static Shield* create(const std::string& filename);

	// Destructor
	virtual ~Shield(){ this->shieldCleanUp(); };

	// Init 
	virtual bool init();

	// Clean Up
	virtual void shieldCleanUp();

	// Return PowerUp Type
	EPowerUpsType getType(){ return m_eType; };

	// Set PowerUp Type
	void setType(EPowerUpsType type){ m_eType = type; };

	// Move Shield
	void moveSprite();

	// Add Particle
	void addParticle();

	// Add Sprite
	void addSprite();

	// Update
	void update();


};

#endif

