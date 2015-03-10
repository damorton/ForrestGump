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
	void addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration);
	void endGame();
	void resetCoins();
	bool isGod(){ return m_bGodMode; };

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
	ParticleSystem* m_pGameObjectEmitter;
	Sprite* m_pJetpack;
	bool m_bGodMode;	
};

#endif
