#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "cocos2d.h"
#include "Popup.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer, public TextFieldDelegate
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    
	virtual ~MainMenu(){ this->mainMenuCleanup(); };
	CREATE_FUNC(MainMenu);

	void playGame(Ref *pSender);
	void leaderboard(Ref *pSender);
	void settings(Ref *pSender);	
	void back(CCObject* pSender);
	void sound(CCObject* pSender);
	void addParticlesToButtons(MenuItemImage* button);
	void mainMenuCleanup();
		
	void createTF();

	// Layer 
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	void keyboardWillShow(IMEKeyboardNotificationInfo &info);
	void keyboardWillHide(IMEKeyboardNotificationInfo &info);

	// TextFieldDelegate
	virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldDetachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldInsertText(TextFieldTTF *pSender, const char *text, size_t nLen) override;
	virtual bool onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, size_t nLen) override;
	virtual bool onDraw(TextFieldTTF * pSender);

	void callbackRemoveNodeWhenDidAction(Node * node);

private:
	MenuItemImage* soundButton;
	bool soundEnabled;
	Popup* popupSettings;
	TextFieldTTF *m_pTextField;
	Action *m_pTextFieldAction;
	bool m_bAction;
	int m_nCharLimit;
	Vec2  m_beginPos;
};

#endif 


