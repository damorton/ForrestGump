#ifndef __PARALLAX_H__
#define __PARALLAX_H__

#include "cocos2d.h"

	USING_NS_CC;

class Parallax
{
	public:		
		/*
		Initialize the Parallax class
		*/
		virtual bool init();

		static Parallax* getInstance();

		// Update my background scrolling
		void scrollBackground(Sprite* bck1, Sprite* bck2, float speed);

private:
	static Parallax* m_pInstance;
};

#endif // __PARALLAX_H__
