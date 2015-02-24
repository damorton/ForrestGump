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
	void setUsername(const char* name);
	void addScore(const char* value);
	void addDistanceScore(const char* value);
	std::shared_ptr<Username> getUsername();
	std::shared_ptr<std::vector<Score>> getScores();

private:
	std::shared_ptr<Username> m_spUsername;
	std::shared_ptr<std::vector<Score>> m_vpScores;
};

#endif