#ifndef _USERNAME_
#define _USERNAME_
#include "TextItem.h"

class Username : public TextItem 
{
public:
	Username(){}
	Username(std::string thisText){setText(thisText.c_str());}
	~Username(){}	
private:
};


#endif