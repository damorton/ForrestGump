#ifndef ENEMYFACTORY_H_
#define	ENEMYFACTORY_H_

#include <memory>
#include "Enemy.h"

typedef std::shared_ptr<Enemy> spEnemy;

class IEnemyFactory
{
public:
	virtual bool init() = 0;
	virtual spEnemy createEnemy() = 0;
	virtual void enemyFactoryCleanp() = 0;
};

class EnemyFactory : public IEnemyFactory
{
public:
	EnemyFactory(){ this->init(); };
	virtual ~EnemyFactory(){ this->enemyFactoryCleanp(); };
	bool init();	
	void enemyFactoryCleanp();
	spEnemy createEnemy();
};
#endif

