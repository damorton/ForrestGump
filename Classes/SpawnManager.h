#ifndef SPAWNMANAGER_H_
#define SPAWNMANAGER_H_

#include "cocos2d.h"

class SpawnManager : public cocos2d::Layer
{
public:
	/*
	Initialize the SpawnManager layer
	*/
	virtual bool init();
	virtual ~SpawnManager(){};
	void update();

	/*
	Initialize the parent node
	*/
	CREATE_FUNC(SpawnManager);

private:
	
};

#endif