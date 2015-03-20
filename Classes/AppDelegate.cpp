#include "AppDelegate.h"
#include "Definitions.h"
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

void AppDelegate::initGLContextAttrs()
{
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	
	//////////////

	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Grand Theft Muffins");
		director->setOpenGLView(glview);
	}

	director->setOpenGLView(glview);

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	// a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
#endif

	Size frameSize = glview->getFrameSize();

	std::vector<std::string> searchPath;
	
	if (frameSize.height > mediumResource.size.height)
	{
		CCLOG("Using large resources");
		searchPath.push_back(largeResource.directory);
		director->setContentScaleFactor(MIN(largeResource.size.height / designResolutionSize.height, largeResource.size.width / designResolutionSize.width));
	}
	else if (frameSize.height > smallResource.size.height)
	{
		CCLOG("Using medium resources");
		searchPath.push_back(mediumResource.directory);
		director->setContentScaleFactor(MIN(mediumResource.size.height / designResolutionSize.height, mediumResource.size.width / designResolutionSize.width));
	}
	else
	{
		CCLOG("Using small resources");
		searchPath.push_back(smallResource.directory);
		director->setContentScaleFactor(MIN(smallResource.size.height / designResolutionSize.height, smallResource.size.width / designResolutionSize.width));
	}
	
	// set searching path
	FileUtils::getInstance()->setSearchPaths(searchPath);

	// turn on display FPS
	director->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//////////////

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
