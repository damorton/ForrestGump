/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

Parallax.h

Description: Moves the background images.
*/

#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Parallax : public cocos2d::LayerColor
{
	public:		

		/* @brief Init function that creates our parallax element */
		virtual bool init();

		/* @brief Initialize the parent node */
		CREATE_FUNC(Parallax);

		/* @brief Parallax deconstructor */
		virtual ~Parallax(){ this->parallaxCleanup(); };
		void parallaxCleanup();

		/* @brief Set the speed of background movement */
		float m_fSpeed;

		/* @brief Background's Sprites */
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

		/* @brief Add the backgrounds to the parallax layer */
		bool addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3, const std::string& filename4, const std::string& filename5);
		
		/* @brief Call the scroll function passing the background images */
		void update();
		
		/* @brief Function scrollBackground move the whole background images using a preset speed */
		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);		
};

#endif // __PARALLAX_H__
