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
		
	auto screenSize = glview->getFrameSize(); // get the devices screen size
	auto designSize = cocos2d::Size(480, 320); // design resolution

	auto fileUtils = FileUtils::getInstance(); // get the file utilities
	std::vector<std::string> resourceDir; // add the file path for resources for the file utilities
	
	// galaxy s4 resources 1920x1080
	if (screenSize.height > mediumResource.size.height)
	{
		resourceDir.push_back(largeResource.directory);	
		resourceDir.push_back(mediumResource.directory);
		resourceDir.push_back(smallResource.directory);
		director->setContentScaleFactor(largeResource.size.height / designSize.height);
	}
	else if (screenSize.height > smallResource.size.height)
	{
		resourceDir.push_back(mediumResource.directory);
		resourceDir.push_back(smallResource.directory);
		director->setContentScaleFactor(mediumResource.size.height / designSize.height);
	}
	// nexus 7 resources 1280x800
	else
	{
		resourceDir.push_back(smallResource.directory);
		director->setContentScaleFactor(smallResource.size.height / designSize.height);
	}

	// add the directories to the file utilities
	fileUtils->setSearchPaths(resourceDir);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	// a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
#endif

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
