#include "User.h"

User::User()
{
	text = std::shared_ptr<StoryText>(new StoryText());
	choices = std::shared_ptr<std::vector<StoryChoice>>(new std::vector<StoryChoice>());
}

User::~User()
{

}

void User::setStoryText(const char* storyText)
{
	text->setText(storyText);
}


void User::addStoryChoice(const char* storyChoice)
{
	
	choices->push_back(StoryChoice(std::string(storyChoice)));
}

std::shared_ptr<StoryText> User::getStoryText()
{
	return text;
}

std::shared_ptr<std::vector<StoryChoice>> User::getStoryChoices()
{
	return choices;
}