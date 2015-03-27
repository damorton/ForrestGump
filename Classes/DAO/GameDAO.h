/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.
	
	GameDAO.h

	Description: Data access object used to interface with database implementations. 
	XML implmenetation uses a local XML file to stored game data and player information.
	The MySQL implementation communicates with a remote apache server allowing access to 
	a MySQL database using PHP5 to control communications between the game the database. 
*/

#ifndef GAMEDAO_
#define GAMEDAO_

#include "User.h"
#include "network\HttpClient.h"

/*
	Abstract classes for XML and MySQL data access objects using
	CRUD. These serve as interfaces to the DAO objects. 
*/
class IGameDAO
{
public:
	virtual ~IGameDAO(){};

	// Create 
	virtual void create() = 0;

	// Read 
	virtual std::shared_ptr<std::vector<User>> read() = 0;

	// Update
	virtual void update(std::shared_ptr<std::vector<User>> Users) = 0;

	// Delete
	virtual void del() = 0;
private:

};

class IGameDAOMySQL
{
public:
	virtual ~IGameDAOMySQL(){};

	// Create
	virtual void create() = 0;

	// Read
	virtual void read(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) = 0;

	// Update
	virtual void update(std::string requestString) = 0;

	// Delete
	virtual void del() = 0;
private:

};


/*
	XML file implementation. Uses a local XML file to store 
	game analytics data and player information.
*/
class GameDAO : public IGameDAO
{
public:
	virtual ~GameDAO(){};

	// Create the XML data access object
	void create();

	/*
		Read users from the local XML file

		@return std::shared_ptr<std::vector<User>> vector of users
	*/
	std::shared_ptr<std::vector<User>> read();

	/*
		Update the local XML file

		@param sstd::shared_ptr<std::vector<User>> Users, vector of users and scores
	*/
	void update(std::shared_ptr<std::vector<User>> Users);

	// Delete data from the XML file
	void del();
private:

};

/*
	Remote MySQL database Implementation. Communicates with the remote
	apache server to store game analytics data into a MySQL database. 
*/
class GameDAOMySQL : public IGameDAOMySQL
{
public:
	virtual ~GameDAOMySQL(){};

	// Create user in database
	void create();

	/*
		Read http response from the server

		@param cocos2d::network::HttpClient *sender, the calling function on callback
		@param cocos2d::network::HttpResponse *response, the response message from the server
	*/
	void read(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

	/*
		Update the remote database
	
		@param std::string requestString, server request message
	*/
	void update(std::string requestString);

	// Delete data from remote database
	void del();
private:

};
#endif