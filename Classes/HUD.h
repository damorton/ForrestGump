#ifndef HUD_H_
#define	HUD_H_

#include "cocos2d.h"

USING_NS_CC;

class HUD : public cocos2d::Layer
{
public:		
	/*
		Initialize the HUD layer
	*/
	virtual bool init();
		
	void updateScore(int score);

	/*
		Initialize the parent node
	*/
	CREATE_FUNC(HUD);

private:
	int m_iScore;
	LabelTTF* m_lScore;
	
};

#endif