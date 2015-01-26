#ifndef CHARACTER_H_
#define CHARACTER_H_

// includes
#include "GameObject.h"
#include "cocos2d.h"

USING_NS_CC;

class Character : public GameObject
{
protected:
	Sprite* m_pSprite; // cocos Sprite
public:
	Character(){ this->init(); }; // constructor
	~Character(){ this->cleanUp(); }; // deconstructor	
	
	virtual bool init(); // initialization
	virtual void cleanUp(); // delete Character 

	// getters
	virtual cocos2d::Sprite* getSprite(){ return m_pSprite; }; // return sprite info

	// setters
	virtual void setSprite(Sprite* sprite){ m_pSprite = sprite; }; // set sprite info
};

#endif