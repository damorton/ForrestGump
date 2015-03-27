/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	User.h

	Description: User contains a username and a vector of scores. The user is a container 
	to store all of the information related to each player. The user object is used to store
	data using a data access object. 
*/

#ifndef _USER_
#define _USER_

// Includes
#include "Score.h"
#include "Username.h"
#include <vector>
#include <memory>

class User
{
public:
	User();
	~User();
	// Set the players username and scores
	void setUsername(const char* name){ m_spUsername->setText(name); };

	// Add score to the vector
	void addScore(const char* value, const char* name){ m_vpScores->push_back(Score(std::string(value), std::string(name))); };		

	// Getters
	std::shared_ptr<Username> getUsername();
	std::shared_ptr<std::vector<Score>> getScores();

private:
	std::shared_ptr<Username> m_spUsername;
	std::shared_ptr<std::vector<Score>> m_vpScores;
};

#endif