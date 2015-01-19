
#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

// includes
#include <vector>
#include <memory>

// forward declarations
class Player;
class Enemy;
class Boss;

/*
	GameManager is the main controller
*/
class GameManager
{
public:	
	GameManager(){ this->init(); }; // constructor	
	~GameManager(){ this->cleanUp(); }; // deconstructor
	virtual bool init(); // initialization	
	void update(); // // main update method (game loop)
	virtual void cleanUp(); // delete GameManager
		
private:	
	std::shared_ptr<Player> m_pPlayer; // Player
	std::vector<std::shared_ptr<Enemy>> m_pvEnemies; // Enemy vector
	std::shared_ptr<Boss> m_pBoss; // Boss		
};

#endif