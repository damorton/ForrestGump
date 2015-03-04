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
	void touch(const Point& location);	
	void update();

	EGameOjectType getType(){ return m_eType; };
	int getState(){ return m_ePlayerState; };	
	int getDistance(){ return m_nDistance; };
	int getCoins(){ return m_nCoins; };
	int getItems(){ return m_nItems; };
	int getBoosters(){ return m_nBoosters; };
	int getFood(){ return m_nFood; };
	
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };
	void addDistance();
	void addCoin();	
	void addItem();
	void addBooster();
	void addFood();
	void addParticle();
	void addParticleCoins();
	void addParticleMuffins();
	void addParticleBoosters();
	void addParticleItems();
	void addParticleMuffins2();
	void addCoinLossParticle();
	
	CREATE_FUNC(Player);

	//ANIMATION
	void getAnimationWithFrames(int, int, int);
	Animate* animate;
	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING, RUNNING } EPlayerState;
private:	
	EPlayerState m_ePlayerState;
	int m_nDistance;
	int m_nCoins;
	int m_nBoosters;
	int m_nFood;
	int m_nItems;		
	int m_nNumberOfJumps;
	std::string m_strUsername;
	ParticleSystem *ccEmitter;
	ParticleSystem *ccCoinEmitter;
	ParticleSystem *ccMuffinEmitter;
	ParticleSystem *ccBoosterEmitter;
	ParticleSystem *ccItemEmitter;
	ParticleSystem *ccCoinLossEmitter;
	ParticleSystem *ccMuffinEmitter2;

};

#endif
