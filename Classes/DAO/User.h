#ifndef _USER_
#define _USER_

#include "Score.h"
#include "Username.h"
#include <vector>
#include <memory>

class User
{
public:
	User();
	~User();
	void setUsername(const char* Username);
	void addScore(const char* Score);
	std::shared_ptr<Username> getUsername();
	std::shared_ptr<std::vector<Score>> getScores();

private:
	std::shared_ptr<Username> text;
	std::shared_ptr<std::vector<Score>> choices;

};

#endif