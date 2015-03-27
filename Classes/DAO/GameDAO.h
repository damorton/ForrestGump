#ifndef _GAMEDAO_
#define _GAMEDAO_
#include "User.h"

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


//xml implementation
class GameDAO : public IGameDAO
{
public:
	virtual ~GameDAO(){};

	//create
	void create();

	//read
	std::shared_ptr<std::vector<User>> read();

	//update
	void update(std::shared_ptr<std::vector<User>> Users);

	//delete
	void del();
private:

};

// Remote MySQL 
class GameDAOMySQL : public IGameDAO
{
public:
	virtual ~GameDAOMySQL(){};

	//create
	void create();

	//read
	std::shared_ptr<std::vector<User>> read();

	//update
	void update(std::shared_ptr<std::vector<User>> Users);

	//delete
	void del();
private:

};




#endif