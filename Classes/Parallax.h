/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	Parallax.h

	Description: Moves the background images.
*/

#ifndef __PARALLAX_H__
#define __PARALLAX_H__

// Includes
#include "Definitions.h"

// Forward declarations
class WorldManager;

class Parallax : public cocos2d::LayerColor
{
	public:		
		// init function that initialize the parallax class 
		virtual bool init();

		// Initialize the parent node 
		CREATE_FUNC(Parallax);

		// Parallax deconstructor 
		virtual ~Parallax(){ this->parallaxCleanup(); };

		// TODO : Implement clean up function 
		void parallaxCleanup();

		// Set the speed of background movement 
		float m_fSpeed;

		// Background's Sprites 
		Sprite* m_pSpriteBackgroundFirst;
		Sprite* m_pSpriteBackgroundFirst1;
		Sprite* m_pSpriteBackgroundSecond;
		Sprite* m_pSpriteBackgroundSecond1;
		Sprite* m_pSpriteBackgroundThird;
		Sprite* m_pSpriteBackgroundThird1;
		Sprite* m_pSpriteBackgroundFourth;
		Sprite* m_pSpriteBackgroundFourth1;
		Sprite* m_pSpriteFloor1;
		Sprite* m_pSpriteFloor2;

		// Add the backgrounds to the parallax layer 
		bool addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3, const std::string& filename4, const std::string& filename5);

		// Call the scroll function passing the background images 
		void update();

		// Function scrollBackground move the whole background images using a preset speed 
		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);
private:
		// World Manager pointer 
		WorldManager* m_pWorldManager;
};

#endif // __PARALLAX_H__
