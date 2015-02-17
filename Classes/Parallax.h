#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Parallax : public cocos2d::LayerColor
{
	public:		

		//Variables
		float m_fSpeed;

		//Sprites
		Sprite* m_pSpriteBackgroundFirst;
		Sprite* m_pSpriteBackgroundFirst1;
		Sprite* m_pSpriteBackgroundSecond;
		Sprite* m_pSpriteBackgroundSecond1;
		Sprite* m_pSpriteBackgroundThird;
		Sprite* m_pSpriteBackgroundThird1;

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
		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);		

};

#endif // __PARALLAX_H__
