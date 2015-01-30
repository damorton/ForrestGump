#include "AppDelegate.h"
#include "SplashScene.h"
#include <string>

USING_NS_CC;

typedef struct tagResource
{
	Size size;
	std::string directory;
}Resource;

static Resource smallResource = { Size(480, 320), "small" };
static Resource mediumResource = { Size(1024, 768), "medium" };
static Resource largeResource = { Size(2048, 1536), "large" };

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
	
	//glview->setFrameSize(960, 640);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
		
	auto screenSize = glview->getFrameSize(); // get the devices screen size
	auto designSize = cocos2d::Size(480, 320); // design resolution

	auto fileUtils = FileUtils::getInstance(); // get the file utilities
	std::vector<std::string> resourceDir; // add the file path for resources for the file utilities
	
	if (2048 == screenSize.width || 2048 == screenSize.height)
	{
		resourceDir.push_back("ipadhd");
		resourceDir.push_back("ipad");
		resourceDir.push_back("iphonehd5");
		resourceDir.push_back("iphonehd");
		resourceDir.push_back("iphone");

		glview->setDesignResolutionSize(2048, 1536, ResolutionPolicy::NO_BORDER);
	}
	else if (1024 == screenSize.width || 1024 == screenSize.height)
	{
		resourceDir.push_back("ipad");
		resourceDir.push_back("iphonehd5");
		resourceDir.push_back("iphonehd");
		resourceDir.push_back("iphone");

		glview->setDesignResolutionSize(1024, 768, ResolutionPolicy::NO_BORDER);
	}
	else if (1136 == screenSize.width || 1136 == screenSize.height)
	{
		resourceDir.push_back("iphonehd5");
		resourceDir.push_back("iphonehd");
		resourceDir.push_back("iphone");

		glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::NO_BORDER);
	}
	else if (960 == screenSize.width || 960 == screenSize.height)
	{
		resourceDir.push_back("iphonehd");
		resourceDir.push_back("iphone");

		glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
	}
	else
	{
		if (screenSize.width > 1080)
		{
			resourceDir.push_back("iphonehd");
			resourceDir.push_back("iphone");

			glview->setDesignResolutionSize(960, 640, ResolutionPolicy::NO_BORDER);
		}
		else
		{
			resourceDir.push_back("iphone");

			glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);
		}
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

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
