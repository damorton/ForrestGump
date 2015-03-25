#ifndef POWERUPS_H_
#define POWERUPS_H_

#include "cocos2d.h"

USING_NS_CC;

class PowerUps 
{
public:
	typedef enum { SHIELD } EPowerUpsType;
	virtual ~PowerUps(){};
	virtual bool init() = 0;
	virtual EPowerUpsType getType() = 0;
	virtual void setType(EPowerUpsType type) = 0;
	
protected:
	EPowerUpsType m_eType;
};

#endif