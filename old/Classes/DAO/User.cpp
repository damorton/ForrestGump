#include "User.h"

User::User()
{
	m_spUsername = std::shared_ptr<Username>(new Username());
	m_vpScores = std::shared_ptr<std::vector<Score>>(new std::vector<Score>());
}

User::~User()
{

}

void User::setUsername(const char* name)
{
	m_spUsername->setText(name);
}


void User::addScore(const char* value)
{	
	m_vpScores->push_back(Score(std::string(value)));
}

void User::addDistanceScore(const char* value)
{
	m_vpScores->push_back(Score(std::string(value)));
}

std::shared_ptr<Username> User::getUsername()
{
	return m_spUsername;
}

std::shared_ptr<std::vector<Score>> User::getScores()
{
	return m_vpScores;
}