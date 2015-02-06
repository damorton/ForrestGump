#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "cocos2d.h"

USING_NS_CC;

class GameObject
{	
public:
	typedef enum { PLAYER, ENEMY, BOSS, ITEM	 } EGameOjectType;	
	virtual bool init() = 0;
	virtual void cleanUp() = 0;	
	virtual EGameOjectType getType() = 0;
	virtual void setType(EGameOjectType type) = 0;
protected:
	EGameOjectType m_eType;
};

#endif