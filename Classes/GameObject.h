#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>
#include "cocos2d.h"

USING_NS_CC;

class GameObject
{	
public:
	typedef enum { OBJECT, WALL, PLAYER, ENEMY, BOSS } EGameOjectType;
	GameObject(){ this->init(); };
	virtual bool init();

	~GameObject(){ this->cleanUp(); };
	virtual void cleanUp();

	std::string getName(){ return m_strName; };
	EGameOjectType getType(){ return m_eType; };

	void setName(std::string name){ m_strName = name; };	
	void setType(EGameOjectType type){ m_eType = type; };
protected:
	std::string m_strName;
	EGameOjectType m_eType;
};

#endif