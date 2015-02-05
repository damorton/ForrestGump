#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include "cocos2d.h"

USING_NS_CC;

class GameObject
{	
public:
	typedef enum { OBJECT, WALL, PLAYER, ENEMY, BOSS } EGameOjectType;
	
	virtual void cleanUp();
	
	EGameOjectType getType(){ return m_eType; };

	void setType(EGameOjectType type){ m_eType = type; };
protected:
	EGameOjectType m_eType;
};

#endif