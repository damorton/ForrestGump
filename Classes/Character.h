#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "GameObject.h"
#include "cocos2d.h"

USING_NS_CC;

class Character : public GameObject
{
protected:
	Sprite* m_pSprite; 
public:
	Character(){ this->init(); }; 
	//virtual bool init();

	virtual ~Character(){ this->cleanUp(); }; 
	virtual void cleanUp();  

	// getters
	virtual cocos2d::Sprite* getSprite(){ return m_pSprite; }; 

	// setters
	virtual void setSprite(Sprite* sprite){ m_pSprite = sprite; }; 
};

#endif