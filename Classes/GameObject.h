#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

class GameObject
{
public:
	typedef enum { OBJECT, WALL, PLAYER, ENEMY, BOSS } EGameOjectType; 	
protected:	
	std::string m_strName; 
	EGameOjectType m_eType; 
public:
	GameObject(){ this->init(); };
	virtual bool init();

	~GameObject(){ this->cleanUp(); };
	virtual void cleanUp();

	std::string getName(){ return m_strName; };
	void setName(std::string name){ m_strName = name; };

	EGameOjectType getType(){ return m_eType; };
	
	void setType(EGameOjectType type){ m_eType = type; };
};

#endif