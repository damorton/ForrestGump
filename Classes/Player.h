#ifndef PLAYER_H_
#define	PLAYER_H_

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

/* ---------------------------------------------------------------------------
** Player.h
**
** Description: Player class which handles player functionality and current state.
**
** Author: Donnchadh Murphy, David Morton, Georgina Sheehan, Tiago Oliveira
**-------------------------------------------------------------------------*/

class Player : public Sprite, public Character
{
public:	
	/* @brief player deconstructor */
	virtual ~Player(){ this->playerCleanup(); };
	/* @brief init function that sets our players initial states and registers the player with the Collision and World Manager */
	virtual bool init();
	/* @brief deallocates player resources */
	void playerCleanup();

	/* defining player actions */
	typedef enum { BOOSTING, JUMPING, RUNNING } EPlayerAction;
	/* defining player jetpack actions */
	typedef enum { BP_UP, BP_DOWN } EBackpackAction;
	/* creating player using filepath */
	static Player* create(const std::string& filename);

	/* @brief player jump function */
	void jump();
	/* @brief deallocates player resources
	   @param point touched
	*/
	void touch(const Point& location);	
	/* @brief player update function, handles state and position*/
	void update();
	/* @brief pauses all player actions */
	void pausePlayer();
	/* @brief resumes all player actions */
	void resumePlayer();
	/* @brief gets game object type
	   @return returns game obkect type
	*/
	EGameOjectType getType(){ return m_eType; };
	/* @brief gets the players current state 
	   @return returns the players current state
	*/
	int getState(){ return m_eState; };
	/* @brief gets the players current action
	   @return returns the players current action
	*/
	int getAction(){ return m_ePlayerAction; }
	/* @brief gets the players high score
	   @return returns the players high score
	*/
	int getHighScore(){ return m_nHighscore; };
	/* @brief gets the players current distance
	   @return returns the players current distance
	*/
	int getDistance(){ return m_nDistance; };
	/* @brief gets the players current coins
	   @return returns the players current coins
	*/
	int getCoins(){ return m_nCoins; };
	/* @brief gets the players current items
	   @return returns the players current items
	*/
	int getItems(){ return m_nItems; };
	/* @brief gets the players current boosters
	   @return returns the players current boosters
	*/
	int getBoosters(){ return m_nBoosters; };
	/* @brief gets the players current food
	   @return returns the players current food
	*/
	int getFood(){ return m_nFood; };
	/* @brief gets the number of enemies killed
	   @return returns the number of enemies killed
	*/
	int getEnemiesKilled(){ return m_nEnemiesKilled; };	
	/* @brief gets the player shield
	   @return returns the shield sprite
	*/
	Sprite* getShield(){ return m_pShield; };
	/* @brief sets the players game object type */
	void setType(EGameOjectType type){ m_eType = type; };
	/* @brief sets the players state */
	void setState(ECharacterState state){ m_eState = state; };
	/* @brief sets the players action */
	void setAction(EPlayerAction action){ m_ePlayerAction = action; };
	/* @brief sets the players jetpacks action */
	void setBPAction(EBackpackAction bpAction){ m_eBackpackAction = bpAction; };
	/* @brief sets the players highscore */
	void setHighscore(int value){ m_nHighscore = value; };
	/* @brief not implemented */
	void addDistance();
	/* @brief adds audio and particle effects to the coin */
	void addCoin();
	/* @brief adds audio and particle effects to the items */
	void addItem();
	/* @brief adds audio and particle effects to the boosters */
	void addBooster();
	/* @brief adds audio and particle effects to the food */
	void addFood();
	/* @brief adds audio and particle effects to killing enemies */
	void addEnemiesKilled(){ m_nEnemiesKilled++; }
	/* @brief adds particle effects */
	void addParticle();
	/* @brief gets path to particles and allows us to edit them 
	   @param path, particle width, particle height, number of particles, effect duration
	*/
	void addParticlesGameObjects(std::string path, float a, float b, int totalPar, float duration);
	/* @brief resets coins */
	void resetCoins();
	/* @brief enables God Mode */
	void setGodMode();
	/* @brief disables God Mode */
	void unsetGodMode();
	/* @brief checks to see if God Mode is enabled
	   @return bool isGod
	*/
	bool isGod(){ return m_bGodMode; };
	/* @brief gets the players animation
	   @param players animation, number of frames
	*/
	void getAnimationWithFrames(char* enemyAnimation, int frames);

	CREATE_FUNC(Player);

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
