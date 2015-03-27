/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	GameOver.h

	Description: The game over class handles with the end of the game. This
	scene is shows up when our hero is caught by an enemy. It displays
	highscore and all the Player Statistics during the game.
*/

#ifndef GAMEOVER_H
#define GAMEOVER_H

// Includes
#include "Definitions.h"

// Forward declarations
class Player;

class GameOver : public cocos2d::Layer
{
public:

	// Creates the Game Over scene 
	static cocos2d::Scene* createScene();

	// Init function that Initialize the main menu class
	virtual bool init();	

	// Initialize the parent node
	CREATE_FUNC(GameOver);

	// Bool variable to check if Game Over scene is initialized
	bool initializeGameOverScene();	

	// Display 
	void displayPlayerStatistics();
	void initLabelWithValue(Label* label, Label* value, Label* statsLabel);
	void displayLeaderboard();
	void updateLocalDB();
	void resume(Ref *pSender);
	void mainMenu(Ref *pSender);
	void exit(Ref *pSender);
	void playAgain(Ref *pSender);

private:
	Size m_Size;
	Vec2 m_Origin;
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	int m_nBoosters;
	int m_nFood;
	int m_nTotalScore;
	Label* m_pCoinsValueLabel;
	Label* m_pItemsValueLabel;
	Label* m_pBoostersValueLabel;
	Label* m_pFoodValueLabel;
	Label* m_newHighscore;
	Label* m_pDistanceValueLabel;
	Player *m_pPlayer;
	
};

#endif 