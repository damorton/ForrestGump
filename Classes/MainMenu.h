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

#include "Definitions.h"

class Popup;

class MainMenu : public cocos2d::Layer, public TextFieldDelegate
{
public:

	/* @brief Creates the Main Menu scene */
    static cocos2d::Scene* createScene();

	/* @brief Init function that Initialize the main menu class */
    virtual bool init();    

	/* @brief Main Menu deconstructor */
	virtual ~MainMenu(){ this->mainMenuCleanup(); };

	/* @brief Initialize the parent node */
	CREATE_FUNC(MainMenu);

	/* @brief Call the Game Scene */
	void playGame(Ref *pSender);
	
	/* @brief TODO : Implement leaderboard scene */
	void leaderboard(Ref *pSender);

	/* @brief TODO : Implement leaderboard scene */
	void settings(Ref *pSender);	

	/* @brief TODO : Implement back button from settings/leaderboard sprite scene */
	void back(CCObject* pSender);
	
	/* @brief TODO : Implement dis/able sound game effects */
	void sound(CCObject* pSender);

	/* @brief Add effects to the Play button */
	void addParticlesToButtons(MenuItemImage* button);

	/* @brief TODO : Implement clean up function */
	void mainMenuCleanup();

	/* @brief User enter his name to save the score */
	void createTF();

	/* @brief Event listener, listen to touches on screen */
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
	/* @brief TODO : Implement dis/able sound game effects */
	MenuItemImage* soundButton;

	/* @brief Play button, starts Game Scene */
	MenuItemImage* m_pPlayButton;

	/* @brief TODO : Implement Popup Settings menu */
	Popup* popupSettings;

	/* @brief Pointer to the user's enter details Text Field TTF */
	TextFieldTTF *m_pTextField;

	/* @brief Max amount of characters allowed */
	int m_nCharLimit;
};

#endif 


