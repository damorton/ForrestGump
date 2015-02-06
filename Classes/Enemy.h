#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite, public Character
{
public:		
	static Enemy* create(const std::string& filename);
	bool init(); // initialize the enemy		
	void cleanUp(); // house keeping 
	void runAI(); // run Enemy AI
	void update(); // update the Enemy
	EGameOjectType getType(){ return m_eType; };	
	void setType(EGameOjectType type){ m_eType = type; };	
	CREATE_FUNC(Enemy);
};

#endif