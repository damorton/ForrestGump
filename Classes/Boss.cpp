
#include <iostream>
#include "Boss.h"

bool Boss::init()
{	
#ifdef _DEBUG
	CCLOG("Boss::init()");
#endif
	// initialize boss
	setType(EGameOjectType::BOSS);
	setName("Boss");
	return true;
}

/* Run Boss AI */
void Boss::runAI()
{
	// run the Boss AI
	CCLOG("Running Boss AI");
}

/* Update the Boss */
void Boss::update()
{
	// update the Boss
	CCLOG("Updating Boss");
}

/* Boss clean up */
void Boss::cleanUp()
{	
}
