#include "User.h"

User::User()
{
	m_spUsername = std::shared_ptr<Username>(new Username());
	m_vpScores = std::shared_ptr<std::vector<Score>>(new std::vector<Score>());
}

User::~User()
{

}

std::shared_ptr<Username> User::getUsername()
{
	return m_spUsername;
}

std::shared_ptr<std::vector<Score>> User::getScores()
{
	return m_vpScores;
}