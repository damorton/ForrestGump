/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Shield.h

Description: Creates a shield object which inherits from powerUp.h and sprite

*/
#ifndef SHIELD_H_
#define SHIELD_H_

#include "Definitions.h"
#include "PowerUps.h"

class Shield : public Sprite, public PowerUps
{
public:
	// Create
	static Shield* create(const std::string& filename);
<<<<<<< HEAD
    /* @briefdestructor for shield */
	virtual ~Shield(){ this->shieldCleanUp(); };
    /* @brief initialise function */
	virtual bool init();
    /* @brief function to clear memory when shield is deleted */
	virtual void shieldCleanUp();
    /* @brief function to return the power up type */
	EPowerUpsType getType(){ return m_eType; };
    /* @brief function to set the type of powerUp */
	void setType(EPowerUpsType type){ m_eType = type; };
    /* @brief function to move the shield */
	void moveSprite();
    /* @brief function to add the particle to the shield */
	void addParticle();
    /* @brief function to add a sprite to the shield */
	void addSprite();
    /* @brief function to update the shield */
=======

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
>>>>>>> 1188667b8fd50cafdf9fca3b8b1c1726de9edc88
	void update();


};

#endif

