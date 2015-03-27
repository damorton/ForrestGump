/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Player.h

Description: Player is responsible to create our hero.
Details such as collectables items and score are set here.
This class is also responsible for animate themselves.

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

	/* @brief Creates the Player */
	static Player* create(const std::string& filename);

	/* @brief Player deconstructor */
	virtual ~Player(){ this->playerCleanup(); };

	/* @brief Init function that Initialize the player class */
	virtual bool init();

	/* @brief TODO : Implement clean up function */
	void playerCleanup();

	/* @brief Player states */
	typedef enum { BOOSTING, JUMPING, RUNNING } EPlayerAction;

	/* @brief Jetpack direction */
	typedef enum { BP_UP, BP_DOWN } EBackpackAction;
	
	/* @brief Jump action */
	void jump();

	/* @brief Touch position on the screen */
	void touch(const Point& location);	

	/* @brief Update the Player status and animation */
	void update();

	/* @brief Pause Player movements */
	void pausePlayer();

	/* @brief Resume Player movements */
	void resumePlayer();

	/* @brief getType function to specify that any class that inherits from this has to implement this function */
	EGameOjectType getType(){ return m_eType; };

	/* @brief TODO : Implement getState to handle with Player states */
	int getState(){ return m_eState; };

	/* @brief Return action in execution */
	int getAction(){ return m_ePlayerAction; }
	
	/* @brief Getters for collectables in game */
	int getHighScore(){ return m_nHighscore; };
	int getDistance(){ return m_nDistance; };
	int getCoins(){ return m_nCoins; };
	int getItems(){ return m_nItems; };
	int getBoosters(){ return m_nBoosters; };
	int getFood(){ return m_nFood; };
	int getEnemiesKilled(){ return m_nEnemiesKilled; };	

	/* @brief Takes the shield buff */
	Sprite* getShield(){ return m_pShield; };

	/* @brief Setters for control hero actions and state moves changes */
	void setType(EGameOjectType type){ m_eType = type; };
	void setState(ECharacterState state){ m_eState = state; };
	void setAction(EPlayerAction action){ m_ePlayerAction = action; };
	void setBPAction(EBackpackAction bpAction){ m_eBackpackAction = bpAction; };

	/* @brief Set the highestest score into player */
	void setHighscore(int value){ m_nHighscore = value; };

	/* @brief TODO : Implement bonus by distance traveled */
	void addDistance();

	/* @brief Add Coins collected as points to Player score */
	void addCoin();

	/* @brief Add Items collected as points to Player score */
	void addItem();

	/* @brief Add Booster collected as points to Player score */
	void addBooster();

	/* @brief Add Food collected as points to Player score */
	void addFood();

	/* @brief Add Enemy killed as points to Player score */
	void addEnemiesKilled(){ m_nEnemiesKilled++; }
	
	/* @brief Add Particle Effects on Player */
	void addParticle();

	/* @brief Add Particle Effects on the Collectables objects */
	void addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration);

	/* @brief Add the Enemies death effects */
	void addEnemyDeathParticle();

	/* @brief Activate god mode when shield buff is taken */
	void setGodMode();

	/* @brief Desactivate the god mode */
	void unsetGodMode();

	/* @brief Check if the mode god is valid */
	bool isGod(){ return m_bGodMode; };

	/* @brief Create and execute the hero animation  */
	void getAnimationWithFrames(char* enemyAnimation, int frames);

private:	
	/* @brief Player and Backpack objects */
	EPlayerAction m_ePlayerAction;
	EBackpackAction m_eBackpackAction;

	/* @brief Variables to store the collectables points */
	int m_nHighscore;
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	int m_nBoosters;
	int m_nFood;
	int m_nEnemiesKilled;
	
	
	/* @brief God mode count */
	int m_nCount;

	/* @brief User name from local DB */
	std::string m_strUsername;

	/* @brief Particles effects for jetpack and objects collectables */
	CCParticleSystem *m_pEmitter;
	CCParticleSystem *m_pGameObjectEmitter;	

	/* @brief Bool check if the mode god is valid */
	bool m_bGodMode;

	/* @brief Shield sprite */
	Sprite* m_pShield;

	/* @brief Jetpack sprite */
	Sprite* m_pJetpack;
};

#endif
