#ifndef HUD_H_
#define	HUD_H_

#include "cocos2d.h"

USING_NS_CC;

class HUD : public cocos2d::Layer
{
public:		
	virtual bool init();		
	void addScore();
	void update();
	void pauseGame(cocos2d::Ref *pSender);
	CREATE_FUNC(HUD);
private:
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	Label* m_pDistanceValueLabel;
	Label* m_lCoinsValueLabel;
	Label* m_lItemsValueLabel;
};

#endif