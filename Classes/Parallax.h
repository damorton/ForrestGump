#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Parallax : public cocos2d::Layer
{
	public:		
		/*
		Initialize the Parallax class
		*/
		virtual bool init();
		
		static Parallax* getInstance();	

		/*
		Add a background to the parallax layer
		*/
		bool addBackground(const std::string& filename);

		// Update my background scrolling
		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);

		// Call the scroll function passing the background images
		void updateBackground();

		// sprites
		Sprite* m_pSpriteBackgroundFirst;
		Sprite* m_pSpriteBackgroundFirst1;
		Sprite* m_pSpriteBackgroundSecond;
		Sprite* m_pSpriteBackgroundSecond1;
		Sprite* m_pSpriteBackgroundThird;
		Sprite* m_pSpriteBackgroundThird1;

		// variables
		float m_fSpeed;
		

private:
	Parallax* m_pParallax;
	// layers	
	
};

#endif // __PARALLAX_H__
