#include "AppDelegate.h"
#include "Splash.h"
#include <string>

USING_NS_CC;

typedef struct tagResource
{
	cocos2d::CCSize size;
	char directory[100];
}Resource;

static Resource smallResource = { cocos2d::CCSizeMake(480, 320), "iphone" };
static Resource smallHDResource = { cocos2d::CCSizeMake(960, 640), "iphonehd" };
static Resource mediumResource = { cocos2d::CCSizeMake(1024, 768), "ipad" };
static Resource largeResource = { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}



bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) {
        glview = GLView::create("Forrest Gump");	
        director->setOpenGLView(glview);
    }
	
	// Set the design resolution
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

	CCSize frameSize = glview->getFrameSize();
	
	auto fileUtils = FileUtils::getInstance(); // get the file utilities
	std::vector<std::string> resourceDir; // add the file path for resources for the file utilities

	// if the frame's height is larger than the height of medium resource size, select large resource.
	if (frameSize.height > mediumResource.size.height)
	{
		resourceDir.push_back(largeResource.directory);
		director->setContentScaleFactor(largeResource.size.height / designResolutionSize.height);
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else if (frameSize.height > smallHDResource.size.height)
	{
		resourceDir.push_back(mediumResource.directory);
		director->setContentScaleFactor(mediumResource.size.height / designResolutionSize.height);
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else if (frameSize.height > smallResource.size.height)
	{
		resourceDir.push_back(smallHDResource.directory);
		director->setContentScaleFactor(smallHDResource.size.height / designResolutionSize.height);
	}
	// if the frame's height is smaller than the height of medium resource size, select small resource.
	else
	{
		resourceDir.push_back(smallResource.directory);
		director->setContentScaleFactor(smallResource.size.height / designResolutionSize.height);
	}
		

	fileUtils->setSearchPaths(resourceDir);

    // create a scene. it's an autorelease object
    auto scene = Splash::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	    
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
