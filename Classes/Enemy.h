#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite, public Character
{
public:		
	static Enemy* create(const std::string& filename);
	virtual ~Enemy(){};
	bool init(); // initialize the enemy		
	void cleanUp(); // house keeping 
	void runAI(); // run Enemy AI
	void update(); // update the Enemy
	EGameOjectType getType(){ return m_eType; };
	int getState(){ return m_eState; };
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(ECharacterState state){ m_eState = state; };

	//ANIMATION
	void getAnimationWithFrames(int, int, int);
	void animateEnemy();
	Animate* animate;

};

#endif