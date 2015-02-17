#ifndef _NODE_
#define _NODE_
#include <memory>

class Node
{

public:
	static std::shared_ptr<Node> create();
	static std::shared_ptr<Node> create(int pX, int pY);
	static std::shared_ptr<Node> create(bool isFlipped);
	static std::shared_ptr<Node> create(int pX,int pY, bool isFlipped);

	int getX(){return x;}
	int getY(){return y;}

	bool initAll(int pX,int pY, bool isFlipped);
	//static std::shared_ptr<Node> instance;
	virtual bool init();
	Node();
	~Node();
private:
	int x;
	int y;
	bool flipped;	
};



#endif