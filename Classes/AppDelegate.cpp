#include "AppDelegate.h"
#include "Splash.h"
#include <string>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview) {
		glview = GLView::create("Forrest Gump");
		director->setOpenGLView(glview);
	}
		
	//glview->setFrameSize(480, 320);

	// turn on display FPS
	//director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	auto screenSize = glview->getFrameSize(); // get the devices screen size
	auto designSize = cocos2d::Size(480, 320); // design resolution

	auto fileUtils = FileUtils::getInstance(); // get the file utilities
	std::vector<std::string> resourceDir; // add the file path for resources for the file utilities

	if (screenSize.height >= 1536)
	{
		CCLOG("using ipadhd 2048x1536");
		resourceDir.push_back("ipadhd");		
		glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
	}
	/*else if (screenSize.height >= 1080)
	{
		CCLOG("using galaxyS4 1920x1080");
		resourceDir.push_back("galaxyS4");
		glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::NO_BORDER);
	}*/
	else if (screenSize.height >= 768)
	{
		CCLOG("using nexus7 1024x768");
		resourceDir.push_back("nexus7");
		glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
	}
	else if (screenSize.height >= 640)
	{
		CCLOG("using iphonehd 960x640");
		resourceDir.push_back("iphonehd");
		glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
	}	
	else
	{
		CCLOG("using iphone 480x320");
		resourceDir.push_back("iphone");
		glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);		
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
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
