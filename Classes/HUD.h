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
	void initLabelWithValue(Label* label, Vec2 position, Label* value);
	CREATE_FUNC(HUD);
private:
	Size m_Size;
	Vec2 m_Origin;	
	float m_fValuePosX;
	int m_nDistance;
	int m_nCoins;
	int m_nItems;
	int m_nBoosters;
	int m_nFood;
	Label* m_pDistanceValueLabel;
	Label* m_pCoinsValueLabel;
	Label* m_pItemsValueLabel;
	Label* m_pBoostersValueLabel;
	Label* m_pFoodValueLabel;
};

#endif