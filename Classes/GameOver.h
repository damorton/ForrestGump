#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();	
	bool initializeGameOverScene();
	void resume(Ref *pSender);
	void mainMenu(Ref *pSender);
	void exit(Ref *pSender);
	void playAgain(Ref *pSender);
	void addStatistics();
	void initLabelWithValue(Label* label, Vec2 position, Label* value);
	CREATE_FUNC(GameOver);
private:
	Size m_Size;
	Vec2 m_Origin;
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