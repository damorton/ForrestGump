#ifndef _USER_
#define _USER_

#include "StoryChoice.h"
#include "StoryText.h"
#include <vector>
#include <memory>

class User
{
public:
	User();
	~User();
	void setStoryText(const char* storyText);
	void addStoryChoice(const char* storyChoice);
	std::shared_ptr<StoryText> getStoryText();
	std::shared_ptr<std::vector<StoryChoice>> getStoryChoices();

private:
	std::shared_ptr<StoryText> text;
	std::shared_ptr<std::vector<StoryChoice>> choices;

};

#endif