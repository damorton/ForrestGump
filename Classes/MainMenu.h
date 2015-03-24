#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "cocos2d.h"
#include "Popup.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer
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
private:
	MenuItemImage* soundButton;
	bool soundEnabled;
	Popup* popupSettings;
};

#endif 

class KeyboardNotificationLayer : public Layer, public IMEDelegate
{
public:
	KeyboardNotificationLayer();
	virtual std::string subtitle() const = 0;
	virtual void keyboadWillShow(IMEKeyboardNotificationInfo& info);

	// Layer 
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchEnded(Touch *touch, Event *event);

protected:
	Vec2 m_beginPos;
};

class TextFieldTTFAction : public KeyboardNotificationLayer, public TextFieldDelegate
{
	TextFieldTTF *m_pTextField;
	Action *m_pTextFieldAction;
	bool m_bAction;
	int m_nCharLimit;

public:
	void callBackRemoveNodeWhenDidAction(Node* node);

	// KeyboardNotificatioLayer
	virtual std::string subtitle() const override;

	// Layer 
	virtual void onEnter() override;
	virtual void onExit() override;

	// TextFieldDelegate
	virtual bool onTextFieldAttachWithIME(TextFieldTTF *sender) override;
	virtual bool onTextFieldDetachWithIME(TextFieldTTF *sender) override;
	virtual bool onTextFieldInsertText(TextFieldTTF *sender, const char *text, size_t nLen) override;
	virtual bool onTextFieldDeleteBackward(TextFieldTTF *sender, const char *delText, size_t nLen) override;
	virtual bool onDraw(TextFieldTTF * sender);

};