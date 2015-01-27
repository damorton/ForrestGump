#include "AppDelegate.h"
#include "SplashScene.h"

USING_NS_CC;

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

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	// a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
#endif

	auto fileUtils = FileUtils::getInstance(); // get the file utilities
	auto screenSize = glview->getFrameSize(); // get the devices screen size
	std::vector<std::string> resourceDir; // add the file path for resources for the file utilities

	// galaxy s4 resources
	if (screenSize.height > nexus7Resource.size.height)
	{
		resourceDir.push_back(s4Resource.directory);

		director->setContentScaleFactor(s4Resource.size.height / designResolutionSize.height);
	}
	// nexus 7 resources
	else
	{
		resourceDir.push_back(nexus7Resource.directory);

		director->setContentScaleFactor(nexus7Resource.size.height / designResolutionSize.height);
	}

	// add the directories to the file utilities
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

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
