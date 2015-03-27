/*
	Copyright (c) 2015 David Morton, Donnchadh Murphy, Georgina Sheehan, Tiago Oliveira

	http://www.grandtheftmuffins.esy.es

	Third year games design and development project. Grand Theft Muffins endless runner game
	written in C++ using the Cocos2dx game engine. http://www.cocos2d-x.org. Back-end game analytics
	and statistics system built using a LAMP stack, Linux, Apache, MySQL and PHP. Hosted locally and remotely.

	AppDelegate.cpp

	Description: AppDelegate is used by Cocos2dx to setup a project on a device. The Window is created using 
	GLView and the resources folders are added to the search directories so that the device resolution can be used
	to create assets that will suit different screen sizes. A scene is created and the singleton director will 
	control the scene management App Delegate is created as standard in all new Cocos2dx projects and only slight 
	modifications are needed to address different device resolutions.	
*/
// Includes
#include <string>
#include <iostream>
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Splash.h"

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
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
#endif	
	Size frameSize = glview->getFrameSize();

	std::vector<std::string> searchPath;
		
	if (frameSize.width > mediumResource.size.width)
	{			
		CCLOG("Using large resources");
		searchPath.push_back(largeResource.directory);
		director->setContentScaleFactor(largeResource.size.width / designResolutionSize.width);		
	}
	else if (frameSize.width > smallResource.size.width)
	{
		CCLOG("Using medium resources");
		searchPath.push_back(mediumResource.directory);
		director->setContentScaleFactor(mediumResource.size.width / designResolutionSize.width);
	}
	else
	{
		CCLOG("Using small resources");
		searchPath.push_back(smallResource.directory);
		director->setContentScaleFactor(smallResource.size.width / designResolutionSize.width);
	}
			
	// set searching path
	FileUtils::getInstance()->setSearchPaths(searchPath);

	// turn on display FPS
	//director->setDisplayStats(true);

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
