#ifndef _SCORE_
#define _SCORE_
#include "TextItem.h"
#include "Node.h"

class Score : public TextItem
{
public:
	Score(){}
	Score(std::string thisText){setText(thisText.c_str());}
	~Score(){}	
private:	
};


#endif