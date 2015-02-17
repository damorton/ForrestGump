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
std::shared_ptr<std::vector<StoryPoint>> GameDAO::read()
{

	//construct a story point vector to pass back
	std::shared_ptr<std::vector<StoryPoint>> storyPointToReturn = std::shared_ptr<std::vector<StoryPoint>>(new std::vector<StoryPoint>());

	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		//doc.Parse(XMLDOC);

		//get the first story element
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		for(tinyxml2::XMLElement* child = root->FirstChildElement(); child != NULL; child =  child->NextSiblingElement())
		{
			StoryPoint tempStoryPoint;
			tempStoryPoint.setStoryText(child->FirstChildElement()->GetText());

			for(tinyxml2::XMLElement* storyChoiceElement = child->FirstChildElement("StoryChoice"); storyChoiceElement != NULL; storyChoiceElement = storyChoiceElement->NextSiblingElement())
			{
				tempStoryPoint.addStoryChoice(storyChoiceElement->GetText());
			}

			storyPointToReturn->push_back(tempStoryPoint);
		}
		return storyPointToReturn;

	}
	return NULL;
}
//update
void GameDAO::update(std::shared_ptr<std::vector<StoryPoint>> storyPoints)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(XMLDOC);

	if(doc.LoadFile(XMLDOC) ==  tinyxml2::XML_SUCCESS)
	{
		doc.Parse(XMLDOC);
		tinyxml2::XMLElement* root = doc.NewElement("Game");
				
		for(int i = 0; i<storyPoints->size(); i++)
		{
			tinyxml2::XMLElement* username = doc.NewElement("Username");
			tinyxml2::XMLElement* score  = doc.NewElement("Score");
			tinyxml2::XMLText* storyText = doc.NewText(storyPoints->at(i).getStoryText()->getText().c_str());
			
			root->InsertEndChild(storyElement);
			storyElement->InsertEndChild(storyTextElement);
			storyTextElement->InsertEndChild(storyText);
			
			//write the story choices
			for(int j = 0; j<storyPoints->at(i).getStoryChoices()->size(); j++)
			{
				tinyxml2::XMLElement* storyChoiceElement = doc.NewElement("StoryChoice");
				//tinyxml2::XMLAttribute* storyTextElement = storyChoiceElement->
				tinyxml2::XMLText* storyChoiceText = doc.NewText(storyPoints->at(i).getStoryChoices()->at(j).getText().c_str());
				storyElement->InsertEndChild(storyChoiceElement);
				storyChoiceElement->InsertEndChild(storyChoiceText);
				
			}

			doc.InsertEndChild(root);

		}
		//doc.Print();
		doc.SaveFile(XMLDOC);
	}
}

//delete
void StoryDAO::del()
{

}