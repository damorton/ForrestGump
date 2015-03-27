/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es
	
	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	GameDAO.cpp

	Description: Data access object used to interface with database implementations.
	XML implmenetation uses a local XML file to stored game data and player information.
	The MySQL implementation communicates with a remote apache server allowing access to
	a MySQL database using PHP5 to control communications between the game the database.
*/
// Includes
#include "GameDAO.h"
#include "Definitions.h"
#include "tinyxml2/tinyxml2.h"
#include "cocos2d.h"
#include "WorldManager.h"

// XML Implementation 
void GameDAO::create()
{		
	// Get a writabel path based on the device
	//std::string filename = cocos2d::FileUtils::getInstance()->fullPathForFilename(XMLDOC);
	std::string writePath = cocos2d::FileUtils::getInstance()->getWritablePath();	
	writePath.append(XMLDOC);

	// Create an XML document, add the first element and save the file
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("Game");
	doc.InsertEndChild(node);
	//doc.SaveFile(filename.c_str());
	doc.SaveFile(writePath.c_str());	
}

std::shared_ptr<std::vector<User>> GameDAO::read()
{
	// Load the XML file
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
		// Get the first user element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			// Create a temporary user to add to the returning vector of users
			User tempUser;
			tempUser.setUsername(child->FirstChildElement()->GetText());
			//CCLOG("%s", child->FirstChildElement()->GetText());
						
			// Start at the first element 'Highscore' and read all scores stored in the XML file
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
	// Load the XML file
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

		// Start at the root node and create hierarchy of elements being stored in the XML file
		tinyxml2::XMLElement* root = doc.NewElement("Game");				
		for(int i = 0; i < Users->size(); i++)
		{
			tinyxml2::XMLElement* userElement = doc.NewElement("User");
			tinyxml2::XMLElement* usernameElement  = doc.NewElement("Username");			

			// Get the players username to store it in the XML file
			tinyxml2::XMLText* username = doc.NewText(Users->at(i).getUsername()->getText().c_str());			
			root->InsertEndChild(userElement);
			userElement->InsertEndChild(usernameElement);
			usernameElement->InsertEndChild(username);
			
			// Write the users scores
			for(int j = 0; j < Users->at(i).getScores()->size(); j++)
			{
				// Update each elements stored in the XML file
				//tinyxml2::XMLElement* scoreElement = doc.NewElement("Score");
				tinyxml2::XMLElement* scoreElement = doc.NewElement(Users->at(i).getScores()->at(j).getName().c_str());
				tinyxml2::XMLText* scoreValue = doc.NewText(Users->at(i).getScores()->at(j).getText().c_str());

				userElement->InsertEndChild(scoreElement);
				scoreElement->InsertEndChild(scoreValue);
				
			}
			doc.InsertEndChild(root);
		}

		// Save the file locally to the devices storage location
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
	// Remote MySQL
	// Update the remote database with POST request
	cocos2d::network::HttpRequest* remoteRequest = new (std::nothrow) cocos2d::network::HttpRequest();

	// Set the remote database URL
	remoteRequest->setUrl("http://grandtheftmuffins.esy.es/update_db.php/");

	// Request type is POST
	remoteRequest->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	remoteRequest->setResponseCallback(CC_CALLBACK_2(GameDAOMySQL::read, this));
	remoteRequest->setRequestData(requestString.c_str(), requestString.length());	

	// Send the request to the PHP script on the server
	cocos2d::network::HttpClient::getInstance()->send(remoteRequest);
	//CCLOG("%s", requestString.c_str());	
	remoteRequest->release();
	/*
	// Local MySQL
	// Update the remote database with POST request
	cocos2d::network::HttpRequest* localRequest = new (std::nothrow) cocos2d::network::HttpRequest();

	// Set the remote database URL
	localRequest->setUrl("http://localhost/update_db.php/");

	// Request type is POST
	localRequest->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	localRequest->setResponseCallback(CC_CALLBACK_2(GameDAOMySQL::read, this));
	localRequest->setRequestData(requestString.c_str(), requestString.length());

	// Send the request to the PHP script on the server
	cocos2d::network::HttpClient::getInstance()->send(localRequest);
	//CCLOG("%s", requestString.c_str());	
	localRequest->release();
	*/
}

void GameDAOMySQL::del()
{
	// Delete record from the remote database
}






