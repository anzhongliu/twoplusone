#include "AppDelegate.h"
#include "StartScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		glview = GLViewImpl::createWithRect("Two Plus One", Rect(0, 0, 270, 480));
#else
		glview = GLViewImpl::create("Two Plus One");
#endif
        
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    // director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

	//预加载声音
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(Resource::music_bg.c_str());
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(Resource::music_bg_2.c_str());
	//预加载音效
	SimpleAudioEngine::getInstance()->preloadEffect(Resource::effect_button.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(Resource::effect_move.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(Resource::effect_move_back.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(Resource::effect_startButton.c_str());
	SimpleAudioEngine::getInstance()->preloadEffect(Resource::effect_toggleButton.c_str());


    // create a scene. it's an autorelease object
    auto scene = StartScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
