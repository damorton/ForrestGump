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

		// Update my background scrolling
		void scrollBackground(CCSprite* bck1, CCSprite* bck2, float speed);

		// Call the scroll function passing the background images
		void updateBackground();

		// sprites
		CCSprite* m_pSpriteBackgroundFirst;
		CCSprite* m_pSpriteBackgroundFirst1;
		CCSprite* m_pSpriteBackgroundSecond;
		CCSprite* m_pSpriteBackgroundSecond1;
		CCSprite* m_pSpriteBackgroundThird;
		CCSprite* m_pSpriteBackgroundThird1;

		// variables
		float m_fSpeed;

		/*
		Initialize the parent node

		//Call the super class theen I can create my .create() from the super class of Layer
		*/
		CREATE_FUNC(Parallax);

		/*
		Add a background to the parallax layer
		*/
		Layer* addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3);
		

private:
	Layer* m_pParallaxLayer;
	Parallax* m_pParallaxcl;
};

#endif // __PARALLAX_H__
