#ifndef SHIELD_H_
#define SHIELD_H_

// header files to be included
#include "PowerUps.h"
#include "cocos2d.h"

/* ---------------------------------------------------------------------------
** Shield.h
**
** Description: Creates a shield object
**
** Author: Donnchadh Murphy, David Morton, Georgina Sheehan, Tiago Oliveira
**-------------------------------------------------------------------------*/

class Shield : public Sprite, public PowerUps
{
public:
	/* @brief function to create a shield */
	static Shield* create(const std::string& filename);
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
	void update();


};

#endif

