#ifndef BOSS_H_
#define BOSS_H_

#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(){ this->init(); }; // constructor
	virtual bool init(); // initialize the Boss

	~Boss(){ this->cleanUp(); }; // deconstructor
	virtual void cleanUp(); 

	virtual void runAI(); // run the Boss AI
	virtual void update(); // update the Boss		
};

#endif