#include "GameDAO.h"
#include "Definitions.h"
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "WorldManager.h"

// XML Implementation 
void GameDAO::create()
{		
	//std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	std::string writePath = cocos2d::FileUtils::getInstance()->getWritablePath();	
	writePath.append(XMLDOC);
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("Game");
	doc.InsertEndChild(node);
	//doc.SaveFile(filename.c_str());
	doc.SaveFile(writePath.c_str());	
}

std::shared_ptr<std::vector<User>> GameDAO::read()
{
	std::shared_ptr<std::vector<User>> UserToReturn = std::shared_ptr<std::vector<User>>(new std::vector<User>());
	//std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	std::string writePath = cocos2d::FileUtils::getInstance()->getWritablePath();
	writePath.append(XMLDOC);
	//CCLOG("filename %s", filename.c_str());
	//CCLOG("writepath %s", writePath.c_str());
	tinyxml2::XMLDocument doc;	
	//doc.LoadFile(filename.c_str());
	doc.LoadFile(writePath.c_str());
		
	//if (doc.LoadFile(filename.c_str()) == tinyxml2::XML_SUCCESS)
	if (doc.LoadFile(writePath.c_str()) == tinyxml2::XML_SUCCESS)
	{
		//get the first user element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			User tempUser;
			tempUser.setUsername(child->FirstChildElement()->GetText());
			//CCLOG("%s", child->FirstChildElement()->GetText());
						
			for(tinyxml2::XMLElement* scoreElement = child->FirstChildElement("Highscore"); scoreElement != NULL; scoreElement = scoreElement->NextSiblingElement())
			{
				//CCLOG("%s %s", scoreElement->GetText(), scoreElement->Name());
				tempUser.addScore(scoreElement->GetText(), scoreElement->Name());
			}		

			UserToReturn->push_back(tempUser);
		}
		return UserToReturn;

	}
	return NULL;
}

void GameDAO::update(std::shared_ptr<std::vector<User>> Users)
{
	//std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	std::string writePath = cocos2d::FileUtils::getInstance()->getWritablePath();
	writePath.append(XMLDOC);
	tinyxml2::XMLDocument doc;
	//doc.LoadFile(filename.c_str());
	doc.LoadFile(writePath.c_str());

	//if (doc.LoadFile(filename.c_str()) == tinyxml2::XML_SUCCESS)
	if (doc.LoadFile(writePath.c_str()) == tinyxml2::XML_SUCCESS)
	{
		//doc.Parse(filename.c_str());
		doc.Parse(writePath.c_str());
		tinyxml2::XMLElement* root = doc.NewElement("Game");
				
		for(int i = 0; i < Users->size(); i++)
		{
			tinyxml2::XMLElement* userElement = doc.NewElement("User");
			tinyxml2::XMLElement* usernameElement  = doc.NewElement("Username");
			
			tinyxml2::XMLText* username = doc.NewText(Users->at(i).getUsername()->getText().c_str());
			
			root->InsertEndChild(userElement);
			userElement->InsertEndChild(usernameElement);
			usernameElement->InsertEndChild(username);
			
			// Write the users scores
			for(int j = 0; j < Users->at(i).getScores()->size(); j++)
			{
				//tinyxml2::XMLElement* scoreElement = doc.NewElement("Score");
				tinyxml2::XMLElement* scoreElement = doc.NewElement(Users->at(i).getScores()->at(j).getName().c_str());
				tinyxml2::XMLText* scoreValue = doc.NewText(Users->at(i).getScores()->at(j).getText().c_str());

				userElement->InsertEndChild(scoreElement);
				scoreElement->InsertEndChild(scoreValue);
				
			}
			doc.InsertEndChild(root);
		}
		//doc.SaveFile(filename.c_str());
		doc.SaveFile(writePath.c_str());
	}
}

void GameDAO::del()
{
	// Delete data from the XML file
}


// MySQL Database Implemntation
void GameDAOMySQL::create()
{		
	// Insert user into database if they are not already there
}

void GameDAOMySQL::read(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	// Read data from HTTPResponse message	
	/*	
	if (response && response->getResponseCode() == 200 && response->getResponseData()) {
	std::vector<char> *data = response->getResponseData();
	std::string ret(&(data->front()), data->size());
	CCLOG("%s", ("Response message: " + ret).c_str());
	}
	else
	{
	CCLOG("%s", ("Error " + std::to_string(response->getResponseCode()) + " in request").c_str()); //error
	}
	*/
	//CCLOG("http request completed");
}

void GameDAOMySQL::update(std::string requestString)
{
	// Update the remote database with POST request
	cocos2d::network::HttpRequest* remoteRequest = new (std::nothrow) cocos2d::network::HttpRequest();
	remoteRequest->setUrl("http://grandtheftmuffins.esy.es/update_db.php/");
	remoteRequest->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	remoteRequest->setResponseCallback(CC_CALLBACK_2(GameDAOMySQL::read, this));
	remoteRequest->setRequestData(requestString.c_str(), requestString.length());	
	cocos2d::network::HttpClient::getInstance()->send(remoteRequest);
	//CCLOG("%s", requestString.c_str());	
	remoteRequest->release();
}

void GameDAOMySQL::del()
{
	// Delete record from the remote database
}






