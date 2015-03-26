#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite, public Character
{
public:		
	CREATE_FUNC(Player);
	virtual ~Player(){ this->playerCleanup(); };
	virtual bool init();
	void playerCleanup();

	typedef enum { BOOSTING, JUMPING, RUNNING } EPlayerAction;
	typedef enum { BP_UP, BP_DOWN } EBackpackAction;
	static Player* create(const std::string& filename);
	
	void jump();
	void touch(const Point& location);	
	void update();

	EGameOjectType getType(){ return m_eType; };
	int getState(){ return m_eState; };
	int getAction(){ return m_ePlayerAction; }
	
	int getHighScore(){ return m_nHighscore; };
	int getDistance(){ return m_nDistance; };
	int getCoins(){ return m_nCoins; };
	int getItems(){ return m_nItems; };
	int getBoosters(){ return m_nBoosters; };
	int getFood(){ return m_nFood; };
	int getEnemiesKilled(){ return m_nEnemiesKilled; };
	

	Sprite* getShield(){ return m_pShield; };

	
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(ECharacterState state){ m_eState = state; };
	void setAction(EPlayerAction action){ m_ePlayerAction = action; };
	void setBPAction(EBackpackAction bpAction){ m_eBackpackAction = bpAction; };

	void setHighscore(int value){ m_nHighscore = value; };
	void addDistance();
	void addCoin();
	void addItem();
	void addBooster();
	void addFood();
	
	void addParticle();
	void addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration);
	void addEnemyDeathParticle();
	void resetCoins();
	void setGodMode();
	void unsetGodMode();
	bool isGod(){ return m_bGodMode; };

	//ANIMATION
	void getAnimationWithFrames(char* enemyAnimation, int frames);

private:	
	EPlayerAction m_ePlayerAction;
	EBackpackAction m_eBackpackAction;

	int m_nHighscore;
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	int m_nBoosters;
	int m_nFood;
	int m_nEnemiesKilled;
	
	
	// God Mode count
	int m_nCount;

	std::string m_strUsername;
	ParticleSystem *m_pEmitter;
	ParticleSystem* m_pGameObjectEmitter;
	Sprite* m_pJetpack;
	bool m_bGodMode;
	Sprite* m_pShield;
};

#endif
