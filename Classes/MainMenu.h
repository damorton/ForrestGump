/*
Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

http://www.grandtheftmuffins.esy.es/

Third year games design and development project. Grand Theft Muffins endless runner game
written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org

MainMenu.h

Description: Main menu placed at the beginning of the game. 
It allows the user to play the game.

*/

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "cocos2d.h"
#include "Popup.h"

USING_NS_CC;

class MainMenu : public cocos2d::Layer, public TextFieldDelegate
{
public:

	/* @brief creates the Main Menu scene */
    static cocos2d::Scene* createScene();

	/* @brief init function that Initialize the main menu class */
    virtual bool init();    

	/* @brief Main Menu deconstructor */
	virtual ~MainMenu(){ this->mainMenuCleanup(); };

	/* @brief Initialize the parent node */
	CREATE_FUNC(MainMenu);

	/* @brief call the Game Scene */
	void playGame(Ref *pSender);
	
	/* @brief TODO : implement leaderboard scene */
	void leaderboard(Ref *pSender);

	/* @brief TODO : implement leaderboard scene */
	void settings(Ref *pSender);	

	/* @brief TODO : implement back button from settings/leaderboard sprite scene */
	void back(CCObject* pSender);
	
	/* @brief TODO : implement dis/able sound game effects */
	void sound(CCObject* pSender);

	/* @brief add effects to the Play button */
	void addParticlesToButtons(MenuItemImage* button);

	/* @brief TODO : implement clean up function */
	void mainMenuCleanup();

	/* @brief user enter his name to save the score */
	void createTF();

	/* @brief event listener, listen to touches on screen */
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);

	/* @brief TODO : Implement keyboard on the screen to user enter details (mobile feature) */
	void keyboardWillShow(IMEKeyboardNotificationInfo &info);
	void keyboardWillHide(IMEKeyboardNotificationInfo &info);

	/* @brief Text field delegate */
	virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldDetachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldInsertText(TextFieldTTF *pSender, const char *text, size_t nLen) override;
	virtual bool onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, size_t nLen) override;
	virtual bool onDraw(TextFieldTTF * pSender);

	/* @brief Remove seq node everytime a new character was input */
	void callbackRemoveNodeWhenDidAction(Node * node);

private:
	/* @brief TODO : implement dis/able sound game effects */
	MenuItemImage* soundButton;

	/* @brief Play button, starts Game Scene */
	MenuItemImage* m_pPlayButton;

	/* @brief TODO : implement Popup Settings menu */
	Popup* popupSettings;

	/* @brief pointer to the user's enter details Text Field TTF */
	TextFieldTTF *m_pTextField;

	/* @brief max amount of characters allowed */
	int m_nCharLimit;
};

#endif 


