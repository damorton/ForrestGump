#include "GameDAO.h"

//create
void GameDAO::create()
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* node = doc.NewElement("Game");
	doc.InsertEndChild(node);
	doc.SaveFile(XMLDOC);
}

//read
std::shared_ptr<std::vector<User>> GameDAO::read()
{

	//construct a story point vector to pass back
	std::shared_ptr<std::vector<User>> UserToReturn = std::shared_ptr<std::vector<User>>(new std::vector<User>());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		//doc.Parse(XMLDOC);

		//get the first story element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			User tempUser;
			tempUser.setUsername(child->FirstChildElement()->GetText());

			for(tinyxml2::XMLElement* ScoreElement = child->FirstChildElement("Score"); ScoreElement != NULL; ScoreElement = ScoreElement->NextSiblingElement())
			{
				tempUser.addScore(ScoreElement->GetText());
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
	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		doc.Parse(XMLDOC);
		tinyxml2::XMLElement* root = doc.NewElement("Game");
				
		for(int i = 0; i<Users->size(); i++)
		{
			tinyxml2::XMLElement* username = doc.NewElement("Username");
			tinyxml2::XMLElement* score  = doc.NewElement("Score");
			tinyxml2::XMLText* Username = doc.NewText(Users->at(i).getUsername()->getText().c_str());
			
			root->InsertEndChild(storyElement);
			storyElement->InsertEndChild(UsernameElement);
			UsernameElement->InsertEndChild(Username);
			
			//write the story choices
			for(int j = 0; j<Users->at(i).getScores()->size(); j++)
			{
				tinyxml2::XMLElement* ScoreElement = doc.NewElement("Score");
				//tinyxml2::XMLAttribute* UsernameElement = ScoreElement->
				tinyxml2::XMLText* ScoreText = doc.NewText(Users->at(i).getScores()->at(j).getText().c_str());
				storyElement->InsertEndChild(ScoreElement);
				ScoreElement->InsertEndChild(ScoreText);
				
			}

			doc.InsertEndChild(root);

		}
		//doc.Print();
		doc.SaveFile(XMLDOC);
	}
}

//delete
void GameDAO::del()
{

}