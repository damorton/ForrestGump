#include "Node.h"

std::shared_ptr<Node> Node::create()
{
	//create our instance to be returned
	std::shared_ptr<Node> pRet(new Node());
	//set up default values 
	

	if(pRet->initAll(0, 0, false))
	{
		//instance = pRet;
		return pRet;

	}
	return NULL;
}

std::shared_ptr<Node> Node::create(int pX, int pY)
{
	//create our instance to be returned
	std::shared_ptr<Node> pRet(new Node());
	//set up default values 
	

	if(pRet->initAll(pX, pY, false))
	{
		//instance = pRet;
		return pRet;

	}
	return NULL;
}
std::shared_ptr<Node> Node::create(bool isFlipped)
{
	//create our instance to be returned
	std::shared_ptr<Node> pRet(new Node());
	//set up default values 
	

	if(pRet->initAll(0, 0, isFlipped))
	{
		//instance = pRet;
		return pRet;

	}
	return NULL;
}
std::shared_ptr<Node> Node::create(int pX,int pY, bool isFlipped)
{
	//create our instance to be returned
	std::shared_ptr<Node> pRet(new Node());
	//set up default values 
	

	if(pRet->initAll(pX, pY, isFlipped))
	{
		//instance = pRet;
		return pRet;

	}
	return NULL;
}
bool Node::initAll(int pX,int pY, bool isFlipped)
{
	x = pX;
	y= pY;
	flipped = isFlipped;

	

	if(init())
	{
		return true;
	}
	return false;
}

bool Node::init()
{


	return true;
}



Node::Node()
{

}

Node::~Node()
{
	//instance._Get_deleter;
	
}

