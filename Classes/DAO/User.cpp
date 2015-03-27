/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	User.cpp

	Description: User contains a username and a vector of scores. The user is a container
	to store all of the information related to each player. The user object is used to store
	data using a data access object.
*/

#include "User.h"

User::User()
{
	m_spUsername = std::shared_ptr<Username>(new Username());
	m_vpScores = std::shared_ptr<std::vector<Score>>(new std::vector<Score>());
}

User::~User()
{
	// Clean up the user object
}

std::shared_ptr<Username> User::getUsername()
{
	return m_spUsername;
}

std::shared_ptr<std::vector<Score>> User::getScores()
{
	return m_vpScores;
}