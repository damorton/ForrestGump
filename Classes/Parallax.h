#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Parallax : public cocos2d::Layer
{
	public:		

		//Variables
		float m_fSpeed;

		//Sprites
		CCSprite* m_pSpriteBackgroundFirst;
		CCSprite* m_pSpriteBackgroundFirst1;
		CCSprite* m_pSpriteBackgroundSecond;
		CCSprite* m_pSpriteBackgroundSecond1;
		CCSprite* m_pSpriteBackgroundThird;
		CCSprite* m_pSpriteBackgroundThird1;

		//Initialize the parent node
		//Call the super class theen I can create my .create() from the super class of Layer
		CREATE_FUNC(Parallax);

		//Initialize the Parallax class		
		virtual bool init();

		//Add a background to the parallax layer		
		bool addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3);
		
		// Call the scroll function passing the background images
		void updateBackground();

		// Update my background scrolling
		void scrollBackground(CCSprite* bck1, CCSprite* bck2, float speed);		

};

#endif // __PARALLAX_H__
