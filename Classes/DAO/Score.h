#ifndef _SCORE_
#define _SCORE_
#include "TextItem.h"

class Score : public TextItem
{
public:
	Score(){}
	Score(std::string thisText){setText(thisText.c_str());}
	Score(std::string thisText, std::string thisName){ setText(thisText.c_str()); setName(thisName.c_str()); }
	~Score(){}	
private:	
};


#endif