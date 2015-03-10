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
		Sprite* m_pSpriteBackgroundFourth;
		Sprite* m_pSpriteBackgroundFourth1;
		Sprite* m_pSpriteFloor1;
		Sprite* m_pSpriteFloor2;



		//Initialize the parent node
		//Call the super class theen I can create my .create() from the super class of Layer
		CREATE_FUNC(Parallax);

		//Initialize the Parallax class		
		virtual bool init();

		virtual ~Parallax(){ this->parallaxCleanup(); };

		//Add a background to the parallax layer		
		bool addBackground(const std::string& filename1, const std::string& filename2, const std::string& filename3, const std::string& filename4, const std::string& filename5);
		
		// Call the scroll function passing the background images
		void update();

		void parallaxCleanup();

		// Update my background scrolling
		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);		
};

#endif // __PARALLAX_H__
