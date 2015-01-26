#include "GameObject.h"

bool GameObject::init()
{
	setName("Game Object");
	setType(EGameOjectType::OBJECT);	
	return true;
}

void GameObject::cleanUp()
{
}
