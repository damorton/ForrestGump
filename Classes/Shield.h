#ifndef SHIELD_H_
#define SHIELD_H_

#include "PowerUps.h"
#include "cocos2d.h"

class Shield : public Sprite, public PowerUps
{
public:
	static Shield* create(const std::string& filename);
	virtual ~Shield(){ this->shieldCleanUp(); };
	virtual bool init();
	virtual void shieldCleanUp();
	EPowerUpsType getType(){ return m_eType; };
	void setType(EPowerUpsType type){ m_eType = type; };
	void moveSprite();


};

#endif

