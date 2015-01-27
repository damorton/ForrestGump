#include "AppDelegate.h"
#include "SplashScene.h"
#include <string>

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

typedef struct tagResource
{
	Size size;
	std::string directory;
}Resource;

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


	auto fileUtils = FileUtils::getInstance();
	auto screenSize = glview->getFrameSize();
	std::vector<std::string> resourceDir;

	//glview->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);

	// check which assets the devices requires
	if (1920 >= screenSize.width || 1920 >= screenSize.height)
	{
		resourceDir.push_back("nexus7");
		resourceDir.push_back("s4");
		
		glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::NO_BORDER);
	}	
	else
	{
		resourceDir.push_back("nexus7");

		glview->setDesignResolutionSize(1280, 800, ResolutionPolicy::NO_BORDER);
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
