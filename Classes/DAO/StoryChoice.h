#ifndef _STORY_CHOICE_
#define _STORY_CHOICE_
#include "TextItem.h"
#include "Node.h"

class StoryChoice : public TextItem
{
public:
	StoryChoice(){}
	StoryChoice(std::string thisText){setText(thisText.c_str());}
	~StoryChoice(){}	
private:	
};


#endif