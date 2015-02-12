#ifndef CHARACTER_H_
#define CHARACTER_H_

class Character
{
public:
	typedef enum { PLAYER, ENEMY, BOSS, ITEM } EGameOjectType;
	virtual ~Character(){};
	virtual bool init() = 0;
	virtual void cleanUp() = 0;
	virtual EGameOjectType getType() = 0;
	virtual void setType(EGameOjectType type) = 0;
protected:
	EGameOjectType m_eType;	
};

#endif