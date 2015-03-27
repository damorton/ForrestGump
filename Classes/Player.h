/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Player.h

Description: 

*/

#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite, public Character
{
public:		

	/* @brief Initialize the parent node */
	CREATE_FUNC(Player);

	/* @brief Player deconstructor */
	virtual ~Player(){ this->playerCleanup(); };

	/* @brief Init function that Initialize the player class */
	virtual bool init();

	/* @brief TODO : Implement clean up function */
	void playerCleanup();

	/* @brief Player states */
	typedef enum { BOOSTING, JUMPING, RUNNING } EPlayerAction;

	/* @brief backpack direction */
	typedef enum { BP_UP, BP_DOWN } EBackpackAction;

	/* @brief Creates the Player */
	static Player* create(const std::string& filename);
	
	/* @brief jump action */
	void jump();

	/* @brief touch position on the screen */
	void touch(const Point& location);	

	/* @brief update the Player status and animation */
	void update();

	/* @brief pause Player movements */
	void pausePlayer();

	/* @brief resume Player movements */
	void resumePlayer();

	/* @brief getType function to specify that any class that inherits from this has to implement this function */
	EGameOjectType getType(){ return m_eType; };

	/* @brief TODO : Implement getState to handle with Player states */
	int getState(){ return m_eState; };

	/* @brief return action in execution */
	int getAction(){ return m_ePlayerAction; }
	
	/* @brief getters for collectables in game */
	int getHighScore(){ return m_nHighscore; };
	int getDistance(){ return m_nDistance; };
	int getCoins(){ return m_nCoins; };
	int getItems(){ return m_nItems; };
	int getBoosters(){ return m_nBoosters; };
	int getFood(){ return m_nFood; };
	int getEnemiesKilled(){ return m_nEnemiesKilled; };	

	/* @brief takes the shield buff */
	Sprite* getShield(){ return m_pShield; };

	
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(ECharacterState state){ m_eState = state; };
	void setAction(EPlayerAction action){ m_ePlayerAction = action; };
	void setBPAction(EBackpackAction bpAction){ m_eBackpackAction = bpAction; };

	void setHighscore(int value){ m_nHighscore = value; };

	/* @brief TODO : Implement bonus by distance traveled */
	void addDistance();

	/* @brief add Coins collected as points to Player score */
	void addCoin();

	/* @brief add Items collected as points to Player score */
	void addItem();

	/* @brief add Booster collected as points to Player score */
	void addBooster();

	/* @brief add Food collected as points to Player score */
	void addFood();

	/* @brief add Enemy killed as points to Player score */
	void addEnemiesKilled(){ m_nEnemiesKilled++; }
	
	/* @brief add Particle Effects on Player */
	void addParticle();

	/* @brief add Particle Effects on the Collectables objects */
	void addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration);

	/* @brief add the Enemies death effects */
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
	CCParticleSystem *m_pEmitter;
	CCParticleSystem *m_pGameObjectEmitter;
	Sprite* m_pJetpack;
	bool m_bGodMode;
	Sprite* m_pShield;
};

#endif
