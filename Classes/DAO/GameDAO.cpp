#include "GameDAO.h"
#include "Definitions.h"
#include "cocos2d\external\tinyxml2\tinyxml2.h"
#include "cocos2d.h"

#define XMLDOC "config/game.xml"

//create
void GameDAO::create()
{		
	std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("Game");
	doc.InsertEndChild(node);
	doc.SaveFile(filename.c_str());
}

//read
std::shared_ptr<std::vector<User>> GameDAO::read()
{

	//construct a story point vector to pass back
	std::shared_ptr<std::vector<User>> UserToReturn = std::shared_ptr<std::vector<User>>(new std::vector<User>());

	std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());

	if (doc.LoadFile(filename.c_str()) == tinyxml2::XML_SUCCESS)
	{
		//get the first user element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			User tempUser;
			tempUser.setUsername(child->FirstChildElement()->GetText());

			for(tinyxml2::XMLElement* scoreElement = child->FirstChildElement("Score"); scoreElement != NULL; scoreElement = scoreElement->NextSiblingElement())
			{
				tempUser.addScore(scoreElement->GetText());
			}

			UserToReturn->push_back(tempUser);
		}
		return UserToReturn;

	}
	return NULL;
}

//update
void GameDAO::update(std::shared_ptr<std::vector<User>> Users)
{
	std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());

	if (doc.LoadFile(filename.c_str()) == tinyxml2::XML_SUCCESS)
	{
		doc.Parse(filename.c_str());
		tinyxml2::XMLElement* root = doc.NewElement("Game");
				
		for(int i = 0; i < Users->size(); i++)
		{
			tinyxml2::XMLElement* userElement = doc.NewElement("User");
			tinyxml2::XMLElement* usernameElement  = doc.NewElement("Username");
			
			tinyxml2::XMLText* username = doc.NewText(Users->at(i).getUsername()->getText().c_str());
			
			root->InsertEndChild(userElement);
			userElement->InsertEndChild(usernameElement);
			usernameElement->InsertEndChild(username);
			
			//write the users scores
			for(int j = 0; j < Users->at(i).getScores()->size(); j++)
			{
				tinyxml2::XMLElement* scoreElement = doc.NewElement("Score");
				tinyxml2::XMLText* scoreValue = doc.NewText(Users->at(i).getScores()->at(j).getText().c_str());
				userElement->InsertEndChild(scoreElement);
				scoreElement->InsertEndChild(scoreValue);
				
			}

			doc.InsertEndChild(root);

		}
		doc.SaveFile(filename.c_str());
	}
}

//delete
void GameDAO::del()
{

}