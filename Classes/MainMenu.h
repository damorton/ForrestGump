/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es/

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.
	MainMenu.h

	Description: Main menu placed at the beginning of the game. 
	It allows the user to play the game.

*/

#ifndef MAINMENU_H_
#define MAINMENU_H_

// Includes
#include "Definitions.h"

// Forward Declarations
class Popup;

class MainMenu : public cocos2d::Layer, public TextFieldDelegate
{
public:

	// Creates the Main Menu scene 
    static cocos2d::Scene* createScene();

	// Init function that Initialize the main menu class
    virtual bool init();    

	// Main Menu deconstructor
	virtual ~MainMenu(){ this->mainMenuCleanup(); };

	// Initialize the parent node
	CREATE_FUNC(MainMenu);

	// Call the Game Scene
	void playGame(Ref *pSender);
	
	// TODO : Implement leaderboard scene
	void leaderboard(Ref *pSender);

	// TODO : Implement leaderboard scene
	void settings(Ref *pSender);	

	// TODO : Implement back button from settings/leaderboard sprite scene 
	void back(CCObject* pSender);
	
	// TODO : Implement dis/able sound game effects
	void sound(CCObject* pSender);

	// Add effects to the Play button
	void addParticlesToButtons(MenuItemImage* button);

	// TODO : Implement clean up function 
	void mainMenuCleanup();

	// User enter his name to save the score 
	void createTF();

	// Event listener, listen to touches on screen 
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);

	// TODO : Implement keyboard on the screen to user enter details (mobile feature) 
	void keyboardWillShow(IMEKeyboardNotificationInfo &info);
	void keyboardWillHide(IMEKeyboardNotificationInfo &info);

	// Text field delegate 
	virtual bool onTextFieldAttachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldDetachWithIME(TextFieldTTF *pSender) override;
	virtual bool onTextFieldInsertText(TextFieldTTF *pSender, const char *text, size_t nLen) override;
	virtual bool onTextFieldDeleteBackward(TextFieldTTF *pSender, const char *delText, size_t nLen) override;
	virtual bool onDraw(TextFieldTTF * pSender);

	// Remove seq node everytime a new character was input 
	void callbackRemoveNodeWhenDidAction(Node * node);

private:
	// TODO : Implement dis/able sound game effects 
	MenuItemImage* soundButton;

	// Play button, starts Game Scene 
	MenuItemImage* m_pPlayButton;

	// TODO : Implement Popup Settings menu 
	Popup* popupSettings;

	// Pointer to the user's enter details Text Field TTF 
	TextFieldTTF *m_pTextField;

	// Max amount of characters allowed 
	int m_nCharLimit;
};

#endif 


