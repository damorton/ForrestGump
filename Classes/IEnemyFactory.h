#ifndef IENEMYFACTORY_H_
#define IENEMYFACTORY_H_

#include <memory>
#include "Enemy.h"

typedef std::shared_ptr<Enemy> spEnemy;

class IEnemyFactory
{
public:	
	
	virtual bool init() = 0;
	virtual spEnemy createEnemy() = 0;
	virtual void cleanUp() = 0;
};

#endif