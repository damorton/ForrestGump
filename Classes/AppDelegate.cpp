#include "AppDelegate.h"
#include "SplashScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

typedef struct tagResource
{
	cocos2d::CCSize size;
	char directory[100];
}Resource;

static Resource nexus7Resource = { cocos2d::CCSizeMake(1280, 800), "nexus7" };
static Resource s4Resource = { cocos2d::CCSizeMake(1920, 1080), "s4" };
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1280, 800);

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

	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	auto fileUtils = FileUtils::getInstance();
	auto screenSize = glview->getFrameSize();
	std::vector<std::string> resourceDir;

	// check which assets the devices requires
	if (screenSize.height > nexus7Resource.size.height)
	{
				
		resourceDir.push_back("s4");		
		resourceDir.push_back("nexus7");
		
		director->setContentScaleFactor(s4Resource.size.height / designResolutionSize.height);
		glview->setDesignResolutionSize(1920, 1080, ResolutionPolicy::NO_BORDER);		

	}	
	else
	{
		resourceDir.push_back("nexus7");

		director->setContentScaleFactor(nexus7Resource.size.height / designResolutionSize.height);
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
