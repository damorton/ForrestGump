#ifndef _TEXT_ITEM_
#define _TEXT_ITEM_
#include <string>

class TextItem 
{
public:
	TextItem(){}
	TextItem(std::string thisText){text = thisText;}
	TextItem(std::string thisText, std::string thisName){ text = thisText; name = thisName; }
	~TextItem(){}
	std::string getText(){return text;}
	std::string getName(){ return name; }
	void setText(const char* newText){text.assign(newText);}	
	void setName(const char* newText){ name.assign(newText); }
private:
	std::string text;	
	std::string name;
};


#endif