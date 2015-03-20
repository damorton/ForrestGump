#include "GameOver.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "Definitions.h"
#include "WorldManager.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	return scene;
}

bool GameOver::init()
{    
    if ( !Layer::init() )
    {
        return false;
    }    
	this->initializeGameOverScene();
    return true;
}

bool GameOver::initializeGameOverScene()
{
	bool success = true;
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm_menu.wav", true);

	m_Size = Director::getInstance()->getVisibleSize();
	m_Origin = Director::getInstance()->getVisibleOrigin();

	m_nDistance = 56754;
	m_nCoins = 234;
	m_nItems = 23;
	m_nBoosters = 6;
	m_nFood = 8906;

	auto gameOverBackground = Sprite::create("background/GameOverBackground.png");
	gameOverBackground->setPosition(Vec2(m_Size.width / 2 + m_Origin.x, m_Size.height / 2 + m_Origin.y));
	this->addChild(gameOverBackground, -50);

	// create the GameOver menu items	
	auto playAgainButton = MenuItemImage::create("buttons/PlayAgainNormal.png", "buttons/PlayAgainClicked.png", CC_CALLBACK_1(GameOver::playAgain, this));
	// position the menu buttons on screen	
	playAgainButton->setPosition(Point((m_Size.width * 0.75), m_Origin.y + PADDING + playAgainButton->getContentSize().height / 2));
	// create menu and add menu items
	auto* menu = Menu::create(playAgainButton, NULL);
	menu->setPosition(Vec2::ZERO);

	this->displayPlayerStatistics();
	this->addChild(menu);

	CCLOG("Game Over initialized");
	return success;
}

void GameOver::displayPlayerStatistics()
{
	int coins = WorldManager::getInstance()->getPlayer()->getCoins();
	int items = WorldManager::getInstance()->getPlayer()->getItems();
	int boosters = WorldManager::getInstance()->getPlayer()->getBoosters();
	int food = WorldManager::getInstance()->getPlayer()->getFood();
	int distance = WorldManager::getInstance()->getPlayer()->getDistance();

	m_nTotalScore = coins + items + boosters + food + distance;

	// Distance
	//auto totalScoreLabel = Label::createWithTTF(WorldManager::getInstance()->getPlayerUsername() + " YOU RAN", LABEL_FONT, LABEL_FONT_SIZE* 1.5);
	auto totalScoreLabel = Label::createWithTTF("TOTAL SCORE", LABEL_FONT, LABEL_FONT_SIZE* 1.5);
	totalScoreLabel->setPosition(Vec2((m_Size.width * 0.25), m_Origin.y + (VISIBLE_SIZE_HEIGHT / 4 )*3 - totalScoreLabel->getContentSize().height / 2));
	totalScoreLabel->setColor(Color3B(255, 255, 255));
	totalScoreLabel->enableGlow(Color4B(255, 255, 51, 255));
	totalScoreLabel->setRotation(-6.0f);
	this->addChild(totalScoreLabel);
	auto totalScoreValue = Label::createWithTTF(std::to_string(m_nTotalScore), LABEL_FONT, LABEL_FONT_SIZE * 4);
	totalScoreValue->setPosition(Vec2(totalScoreLabel->getPositionX(), totalScoreLabel->getPositionY() - PADDING - totalScoreValue->getContentSize().height / 2));
	totalScoreValue->setColor(Color3B(255, 255, 64));
	totalScoreValue->enableGlow(Color4B(255, 255, 51, 255));
	totalScoreValue->setRotation(-6.0f);
	this->addChild(totalScoreValue);
	
	auto newHighscore = Label::createWithTTF("NEW HIGHSCORE!", LABEL_FONT, LABEL_FONT_SIZE);
	newHighscore->setPosition(Vec2(totalScoreValue->getPositionX(), totalScoreValue->getPositionY() - PADDING - totalScoreValue->getContentSize().height / 2 - newHighscore->getContentSize().height / 2));
	newHighscore->setColor(Color3B(255, 0, 0));
	newHighscore->enableGlow(Color4B(255, 255, 51, 255));
	newHighscore->setRotation(-6.0f);
	newHighscore->setVisible(false);
	this->addChild(newHighscore);

	int previousHighscore = std::atoi(WorldManager::getInstance()->getPlayerHighscore().c_str());
	//CCLOG("previous %d", previousHighscore);
	int currentScore = WorldManager::getInstance()->getPlayer()->getDistance();
	//CCLOG("current %d", currentScore);
	if (currentScore > previousHighscore)
	{
		//CCLOG("New higscore recorded!");
		newHighscore->setVisible(true);
		auto scaleUp = ScaleBy::create(.5, 2.0);
		auto scaleDown = ScaleBy::create(.5, 0.5);
		auto scaling = Sequence::create(scaleUp, scaleDown, NULL);
		newHighscore->runAction(scaling);
		this->storeHighscore();
	}
		
	auto statsLabel = Label::createWithTTF("STATISTICS", LABEL_FONT, LABEL_FONT_SIZE * 1.5);	
	statsLabel->setPosition(Point((m_Size.width * 0.75), m_Origin.y + m_Size.height - PADDING - statsLabel->getContentSize().height / 2));
	statsLabel->setColor(Color3B(255, 255, 255));
	statsLabel->enableOutline(Color4B(0, 0, 0, 255));
	statsLabel->enableGlow(Color4B(0, 0, 0, 255));
	this->addChild(statsLabel);
	
	// Distance
	auto distanceLabel = Label::createWithTTF("Distance ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pDistanceValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getDistance()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(distanceLabel, m_pDistanceValueLabel, statsLabel);		

	// Coins
	auto coinsLabel = Label::createWithTTF("Coins ", LABEL_FONT, LABEL_FONT_SIZE);		
	m_pCoinsValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getCoins()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(coinsLabel, m_pCoinsValueLabel, distanceLabel);
	
	// Items
	auto itemsLabel = Label::createWithTTF("Items ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pItemsValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getItems()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(itemsLabel, m_pItemsValueLabel, coinsLabel);
	
	// Boosters
	auto boostersLabel = Label::createWithTTF("Boosters ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pBoostersValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getBoosters()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(boostersLabel, m_pBoostersValueLabel, itemsLabel);

	// Food
	auto foodLabel = Label::createWithTTF("Food ", LABEL_FONT, LABEL_FONT_SIZE);
	m_pFoodValueLabel = Label::createWithTTF(std::to_string(WorldManager::getInstance()->getPlayer()->getFood()), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(foodLabel, m_pFoodValueLabel, boostersLabel);
	
	// Highscore
	auto highScoreLabel = Label::createWithTTF("Highscore ", LABEL_FONT, LABEL_FONT_SIZE);
	auto highScoreValueLabel = Label::createWithTTF(std::to_string(previousHighscore), LABEL_FONT, LABEL_FONT_SIZE);
	this->initLabelWithValue(highScoreLabel, highScoreValueLabel, foodLabel);

	// Duration of session
	// Number of jumps
	// Time on foot
	// Time jumping
	// Enemies dodged
	// Enemies killed	
	
	cocos2d::network::HttpRequest* request = new (std::nothrow) cocos2d::network::HttpRequest();
	request->setUrl("http://grandtheftmuffins.esy.es/test.php/");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(GameOver::onHttpRequestCompleted, this));

	// write the post data
	String *data = String::createWithFormat("username=David&score=%s", std::to_string(m_nTotalScore).c_str());
	request->setRequestData(data->getCString(), data->length());
	request->setTag("myData");
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
	
	//CCLOG("display player stats");
}

void GameOver::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	//CCLOG("http request completed");	
	if (response && response->getResponseCode() == 200 && response->getResponseData()) {
		std::vector<char> *data = response->getResponseData();
		std::string ret(&(data->front()), data->size());
		CCLOG("%s", ("Response message: " + ret).c_str());
	}
	else 
	{
		CCLOG("%s", ("Error " + std::to_string(response->getResponseCode()) + " in request").c_str()); //error
	}
}

void GameOver::initLabelWithValue(Label* label, Label* value, Label* labelAbove)
{	
	label->setPosition(Vec2((m_Size.width / 2) + PADDING + label->getContentSize().width / 2, labelAbove->getPositionY() - labelAbove->getContentSize().height / 2));
	label->setColor(Color3B(200, 200, 200));
	label->enableOutline(Color4B(0, 0, 0, 255));
	label->enableGlow(Color4B(0, 0, 0, 255));
	this->addChild(label);
	value->setPosition(Vec2(m_Size.width - PADDING - value->getContentSize().width / 2, label->getPositionY()));
	value->setColor(Color3B(200, 200, 200));
	value->enableOutline(Color4B(0, 0, 0, 255));
	value->enableGlow(Color4B(0, 0, 0, 255));
	this->addChild(value);
}

void GameOver::storeHighscore()
{
	WorldManager::getInstance()->setPlayerHighscore(std::to_string(m_nTotalScore));
}

void GameOver::displayLeaderboard()
{	
	std::shared_ptr<std::vector<User>> users = WorldManager::getInstance()->getDAO()->read();
	for (int i = 0; i < users->size(); i++)
	{
		CCLOG("%s", users->at(i).getUsername()->getText().c_str());

		for (int j = 0; j < users->at(i).getScores()->size(); j++)
		{
			CCLOG("%s", users->at(i).getScores()->at(j).getText().c_str());
		}
	}
}

void GameOver::playAgain(cocos2d::Ref *pSender)
{
	WorldManager::getInstance()->resetGameWorld();
	CollisionManager::getInstance()->resetCollisionManager();
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/button-21.wav", false, 1.0f, 1.0f, 1.0f);
}

void GameOver::resume(cocos2d::Ref *pSender)
{
    Director::getInstance()->popScene();		
}

void GameOver::mainMenu(cocos2d::Ref *pSender)
{
    auto scene = MainMenu::createScene();    
	Director::getInstance()->replaceScene(TransitionFlipX::create(0,scene));
}

void GameOver::exit(cocos2d::Ref *pSender)
{
	Director::getInstance()->end();
}

