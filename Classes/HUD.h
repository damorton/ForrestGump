#ifndef HUD_H_
#define	HUD_H_

#include "cocos2d.h"

USING_NS_CC;

class HUD : public cocos2d::Layer
{
public:		
	virtual bool init();		
	void updateScore();	
	CREATE_FUNC(HUD);
private:
	int m_iScore;
	Label* m_lScore;
	
};

#endif