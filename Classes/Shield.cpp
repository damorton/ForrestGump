#include "Shield.h"
#include "WorldManager.h"

USING_NS_CC;

Shield* Shield::create(const std::string& filename)
{
	Shield* pSprite = new Shield();

	if (pSprite->initWithFile(filename))
	{
		pSprite->autorelease();
		pSprite->init();
		return pSprite;
	}


	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool Shield::init()
{
	setType(SHIELD);
	return true;

}

void Shield::shieldCleanUp()
{
	
}