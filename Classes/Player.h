#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h"
#include "cocos2d.h"
#include "AnimationMoves.h"

USING_NS_CC;

class Player : public Sprite, public Character
{
public:		
	static Player* create(const std::string& filename);
	virtual ~Player(){};
	bool init();
	void cleanUp();	

	void jump();

	/* 
		Player touch function

		@param Point location of the touch position
	*/
	void touch(const Point& location);	
	void update();

	EGameOjectType getType(){ return m_eType; };
	int getState(){ return m_ePlayerState; };	
	
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };

	void addCoin(){ m_nCoins++; };
	void addDistance(){ m_nDistance++; };
	void addBooster(){ m_nBoosters++; };
	void addFood(){ m_nFood++; };
	void addItem(){ m_nItems++; };

	int getDistance(){ return m_nDistance; };
	int getCoins(){ return m_nCoins; };
	int getItems(){ return m_nItems; };
	

	CREATE_FUNC(Player);
private:
	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING, RUNNING } EPlayerState;
	EPlayerState	m_ePlayerState;
	int m_nDistance;
	int m_nCoins;
	int m_nBoosters;
	int m_nFood;
	int m_nItems;
	
};

#endif