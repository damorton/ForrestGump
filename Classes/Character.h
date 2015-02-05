#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "GameObject.h"
#include "cocos2d.h"

USING_NS_CC;

class Character : public GameObject
{

public:
	virtual void cleanUp();  
};

#endif