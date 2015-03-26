#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite, public Character
{
public:		
	static Enemy* create(const std::string& filename);
	virtual ~Enemy(){ this->enemyCleanUp(); };
	virtual bool init(); 	
	virtual void enemyCleanUp(); 


	void runAI(); // run Enemy AI
	void update(); // update the Enemy
	EGameOjectType getType(){ return m_eType; };
	int getState(){ return m_eState; };
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(ECharacterState state){ m_eState = state; };
	void getRandomSpeed();
	int getSpeed(){ return m_nSpeed; };
	
	//ANIMATION
	void getAnimationWithFrames(char* enemyAnimation, int frames);
	void animateEnemy();
	Animate* animate;
	int m_nSpeed;

};

#endif