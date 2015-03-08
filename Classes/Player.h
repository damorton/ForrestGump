#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite, public Character
{
public:		
	typedef enum { BOOSTING, JUMPING, RUNNING } EPlayerAction;
	typedef enum { BP_UP, BP_DOWN } EBackpackAction;
	static Player* create(const std::string& filename);
	virtual ~Player(){};
	bool init();
	void cleanUp();	
	void jump();
	void touch(const Point& location);	
	void update();

	EGameOjectType getType(){ return m_eType; };
	int getState(){ return m_eState; };
	int getAction(){ return m_ePlayerAction; }
	int getDistance(){ return m_nDistance; };
	int getCoins(){ return m_nCoins; };
	int getItems(){ return m_nItems; };
	int getBoosters(){ return m_nBoosters; };
	int getFood(){ return m_nFood; };
	
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(ECharacterState state){ m_eState = state; };
	void setAction(EPlayerAction action){ m_ePlayerAction = action; };
	void setBPAction(EBackpackAction bpAction){ m_eBackpackAction = bpAction; };
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
	//void addParticles(std::string filename, Point point = Point(0,0), float duration = 0.5f, int numberOfParticles = 5);
	void endGame();
	void resetCoins();

	//ANIMATION
	void getAnimationWithFrames(char* enemyAnimation, int frames);
	CREATE_FUNC(Player);	

private:	
	EPlayerAction m_ePlayerAction;
	EBackpackAction m_eBackpackAction;
	int m_nDistance;
	int m_nCoins;
	int m_nBoosters;
	int m_nFood;
	int m_nItems;		
	int m_nNumberOfJumps;
	std::string m_strUsername;
	ParticleSystem *m_pEmitter;
	ParticleSystem *m_pCoinEmitter;
	ParticleSystem *m_pMuffinEmitter;
	ParticleSystem *m_pMuffinEmitter2;
	ParticleSystem *m_pBoosterEmitter;
	ParticleSystem *m_pItemEmitter;
	ParticleSystem *m_pCoinLossEmitter;

};

#endif
