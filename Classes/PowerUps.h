/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	PowerUps.h

	Description: Creates a PowerUp abstract class 

*/
#ifndef POWERUPS_H_
#define POWERUPS_H_

class PowerUps 
{
public:
	typedef enum { SHIELD } EPowerUpsType; // Enum to hold the type of powerUps

	// Destructor 
	virtual ~PowerUps(){};

	// Pure virtual init function 
	virtual bool init() = 0;

	// Pure virtual getType function 
	virtual EPowerUpsType getType() = 0;

	// Pure virtual set type function
	virtual void setType(EPowerUpsType type) = 0;
	
protected:
	EPowerUpsType m_eType;
};

#endif