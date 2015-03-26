#ifndef SHIELD_H_
#define SHIELD_H_

// header files to be included
#include "PowerUps.h"
#include "cocos2d.h"

// creates shield to inherit from sprite and powerUps 
class Shield : public Sprite, public PowerUps
{
	// public access specifier
public:
	// function to create a shield
	static Shield* create(const std::string& filename);

	// destructor for shield
	virtual ~Shield(){ this->shieldCleanUp(); };

	// initialise function 
	virtual bool init();

	// function to clear memory when shield is deleted
	virtual void shieldCleanUp();

	// function to return the power up type
	EPowerUpsType getType(){ return m_eType; };

	// function to set the type of powerUp
	void setType(EPowerUpsType type){ m_eType = type; };

	// function to move the shield
	void moveSprite();

	// function to add the particle to the shield
	void addParticle();

	// function to add a sprite to the shield
	void addSprite();

	// function to update the shield
	void update();


};

#endif

