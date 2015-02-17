#include "User.h"

User::User()
{
	text = std::shared_ptr<Username>(new Username());
	choices = std::shared_ptr<std::vector<Score>>(new std::vector<Score>());
}

User::~User()
{

}

void User::setUsername(const char* Username)
{
	text->setText(Username);
}


void User::addScore(const char* Score)
{
	
	choices->push_back(Score(std::string(Score)));
}

std::shared_ptr<Username> User::getUsername()
{
	return text;
}

std::shared_ptr<std::vector<Score>> User::getScores()
{
	return choices;
}