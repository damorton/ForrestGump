#ifndef ENEMYFACTORY_H_
#define	ENEMYFACTORY_H_

#include "IEnemyFactory.h"

class EnemyFactory : public IEnemyFactory
{
public:
	EnemyFactory(){ this->init(); };
	~EnemyFactory(){ this->cleanUp(); };
	bool init();	
	void cleanUp();
	spEnemy createEnemy();
};
#endif

