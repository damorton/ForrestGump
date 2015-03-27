#ifndef POWERUPS_H_
#define POWERUPS_H_

// include header files
#include "cocos2d.h"

// using cocos namespace
USING_NS_CC;

// create powerUps class
class PowerUps 
{
	// public access specifier which specifies that these member variables and functions can be
	// accessed from anywhere in the program
public:
	// enum to hold the type of powerUps
	typedef enum { SHIELD } EPowerUpsType;

	// destructor for powerUps
	virtual ~PowerUps(){};

	// pure virtual init function to specify that any class that inherits from this has to implement this function
	virtual bool init() = 0;

	// pure virtual getType function to specify that any class that inherits from this has to implement this function
	// return its type
	virtual EPowerUpsType getType() = 0;

	// pure virtual set type function to specify that any class that inherits from this has to implement this function
	// and set its type
	virtual void setType(EPowerUpsType type) = 0;
	
	// protected access specifier which gives accessibility to classes that inherit from this class
protected:
	// variable for type of powerUp
	EPowerUpsType m_eType;
};

#endif