/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org
	
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

class IGameDAO
{
public:
	virtual ~IGameDAO(){};

	//create
	virtual void create() = 0;

	//read
	virtual std::shared_ptr<std::vector<User>> read() = 0;

	//update
	virtual void update(std::shared_ptr<std::vector<User>> Users) = 0;

	//delete
	virtual void del() = 0;
private:

};

class IGameDAOMySQL
{
public:
	virtual ~IGameDAOMySQL(){};

	//create
	virtual void create() = 0;

	//read
	virtual void read(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) = 0;

	//update
	virtual void update(std::string requestString) = 0;

	//delete
	virtual void del() = 0;
private:

};


// XML implementation
class GameDAO : public IGameDAO
{
public:
	virtual ~GameDAO(){};

	//create
	void create();

	// Read the local XML file
	std::shared_ptr<std::vector<User>> read();

	// Update the MySQL database on the remote server
	void update(std::shared_ptr<std::vector<User>> Users);

	//delete
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